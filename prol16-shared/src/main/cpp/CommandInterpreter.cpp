/**
 * @author		creiterer
 * @date 		2019-09-13
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "CommandInterpreter.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <utility>

namespace util {

CommandInterpreter::CommandInterpreter(std::string prompt)
: quit(false), cont(false), continueCount(1), invocationCount(0), prompt(std::move(prompt)) {
	registerCommand("q", "quit", 0, 0, "", [this](ArgumentVector const& /*unused*/){
		quit = true;
	});

	registerCommand("h", "help", 0, 0, "-- show help", [this](ArgumentVector const& /*unused*/){
		std::unordered_set<StringMap::mapped_type> alreadyCoveredLongNames;

		for (auto const &commandName : shortToLongNameMapping) {
			std::cerr << commandName.first << '|' << commandName.second << ' ' << helpMessageMap.at(commandName.second) << std::endl;
			alreadyCoveredLongNames.emplace(commandName.second);
		}

		for (auto const &command : commandMap) {
			if (alreadyCoveredLongNames.find(command.first) == alreadyCoveredLongNames.cend()) {
				std::cerr << command.first << ' ' << helpMessageMap.at(command.first) << std::endl;
			}
		}
	});
}

void CommandInterpreter::registerCommand(std::string const &commandName,
										 unsigned const minArgCount, unsigned const maxArgCount,
										 std::string const &helpMessage, CommandCallback const &commandCallback,
										 ArgumentValidationFn const &argumentValidationFn) {
	registerCommand("", commandName, minArgCount, maxArgCount, helpMessage, commandCallback, argumentValidationFn);
}

void CommandInterpreter::registerCommand(std::string const &shortCommandName, std::string const &longCommandName,
										 unsigned const minArgCount, unsigned const maxArgCount,
										 std::string const &helpMessage, CommandCallback const &commandCallback,
										 ArgumentValidationFn const &argumentValidationFn) {
	auto result = commandMap.emplace(longCommandName, commandCallback);
	assert(result.second);

	if (!shortCommandName.empty()) {
		auto result2 = shortToLongNameMapping.emplace(shortCommandName, longCommandName);
		assert(result2.second);
	}

	if (argumentValidationFn != nullptr) {
		argumentValidationFnMap.emplace(longCommandName, argumentValidationFn);
	}

	helpMessageMap.emplace(longCommandName, helpMessage);
	argumentCountMap.emplace(longCommandName, std::make_pair(minArgCount, maxArgCount));
}

void CommandInterpreter::registerContinueCommand(std::string const &shortCommandName, std::string const &longCommandName,
												 std::string const &helpMessage) {
	registerCommand(shortCommandName, longCommandName, 0, 1, helpMessage, [this](ArgumentVector const &arguments){
		cont = true;

		if (arguments.size() == 1) {
			continueCount = stoul(arguments.at(0));
		} else {
			continueCount = 1;
		}
	});

}

void CommandInterpreter::run() {
	++invocationCount;
	if (isQuit() || shouldContinue()) {
		return;
	}

	cont = false;
	invocationCount = 0;

	do {
		showPrompt();

		std::string command = getCommand();

		while (!isCommandValid(command)) {
			printInvalidCommandMessage(command);
			showPrompt();
			command = getCommand();
		}

		parseAndExecuteCommand(command);
	} while (!isQuit() && !shouldContinue());
}

bool CommandInterpreter::isCommandValid(std::string const &command) const {
	if (command.empty()) {
		return false;
	}

	ArgumentVector const argumentVector = parseCommand(command);
	std::string const commandName = argumentVector.at(0);
	ArgumentVector const arguments(std::next(argumentVector.cbegin()), argumentVector.cend());

	std::string canonicalCommandName;
	try {
		canonicalCommandName = getCanonicalCommandName(commandName);
	} catch (std::out_of_range const&) {
		return false;
	}

	ArgumentCountRange const argumentCountRange = argumentCountMap.at(canonicalCommandName);
	if ((arguments.size() < argumentCountRange.first) || (arguments.size() > argumentCountRange.second)) {
		return false;
	}

	if (argumentValidationFnMap.find(canonicalCommandName) != argumentValidationFnMap.cend()) {
		return std::all_of(arguments.cbegin(), arguments.cend(), argumentValidationFnMap.at(canonicalCommandName));
	}

	return true;
}

void CommandInterpreter::showPrompt() const {
	std::cerr << prompt;
}

std::string CommandInterpreter::getCommand() const {
	std::string command;
	std::getline(std::cin, command);

	return command;
}

CommandInterpreter::ArgumentVector CommandInterpreter::parseCommand(std::string const &command) {
	ArgumentVector argumentVector;

	if (command.empty()) {
		return argumentVector;
	}

	// split the actual command from its arguments
	size_t pos = command.find(' ');
	argumentVector.push_back(command.substr(0, pos));

	while (pos != std::string::npos) {
		size_t prevPos = pos + 1;
		pos = command.find(' ', prevPos);
		argumentVector.push_back(command.substr(prevPos, pos - prevPos));
	}

	return argumentVector;
}

void CommandInterpreter::parseAndExecuteCommand(std::string const &command) const {
	// command should already be validated at this point
	ArgumentVector const argumentVector = parseCommand(command);
	std::string const commandName = argumentVector.at(0);
	ArgumentVector const arguments(std::next(argumentVector.cbegin()), argumentVector.cend());

	commandMap.at(getCanonicalCommandName(commandName))(arguments);
}

std::string CommandInterpreter::getCanonicalCommandName(std::string const &command) const {
	if (commandMap.count(command) > 0) {
		return command;
	}

	return shortToLongNameMapping.at(command);
}

void CommandInterpreter::printInvalidCommandMessage(std::string const &command) {
	std::cerr << "Invalid command '" << command << "'! Try command 'help'." << std::endl;
}

bool CommandInterpreter::shouldContinue() const {
	return cont && (invocationCount < continueCount);
}

}	// namespace util
