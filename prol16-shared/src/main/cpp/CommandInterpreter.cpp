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

CommandInterpreter::CommandInterpreter(std::string prompt) : quit(false), prompt(std::move(prompt)) {
	registerCommand("q", "quit", "", [this](ArgumentVector const& /*unused*/){
		quit = true;
	});

	registerCommand("h", "help", "-- show help", [this](ArgumentVector const& /*unused*/){
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

void CommandInterpreter::registerCommand(std::string const &commandName, std::string const &helpMessage,
										 CommandCallback const &commandCallback) {
	registerCommand("", commandName, helpMessage, commandCallback);
}

void CommandInterpreter::registerCommand(std::string const &shortCommandName, std::string const &longCommandName,
										 std::string const &helpMessage, CommandCallback const &commandCallback) {
	auto result = commandMap.emplace(longCommandName, commandCallback);
	assert(result.second);

	if (!shortCommandName.empty()) {
		auto result2 = shortToLongNameMapping.emplace(shortCommandName, longCommandName);
		assert(result2.second);
	}

	helpMessageMap.emplace(longCommandName, helpMessage);
}

void CommandInterpreter::run() const {
	if (isQuit()) {
		return;
	}

	showPrompt();

	std::string command = getCommand();

	while (!isCommandValid(command)) {
		printInvalidCommandMessage(command);
		showPrompt();
		command = getCommand();
	}

	parseAndExecuteCommand(command);
}

bool CommandInterpreter::isCommandValid(std::string const &command) const {
	if (command.empty()) {
		return false;
	}

	std::string const commandName = command.substr(0, command.find(' '));

	return (commandMap.find(commandName) != commandMap.cend()) ||
		   (shortToLongNameMapping.find(commandName) != shortToLongNameMapping.cend());
}

void CommandInterpreter::showPrompt() const {
	std::cerr << prompt;
}

std::string CommandInterpreter::getCommand() const {
	std::string command;
	std::getline(std::cin, command);

	return command;
}

void CommandInterpreter::parseAndExecuteCommand(std::string const &command) const {
	// split the actual command from its arguments
	size_t pos = command.find(' ');
	std::string commandName = command.substr(0, pos);

	ArgumentVector arguments;
	while (pos != std::string::npos) {
		size_t prevPos = pos + 1;
		pos = command.find(' ', prevPos);
		arguments.push_back(command.substr(prevPos, pos - prevPos));
	}

	try {
		commandMap.at(commandName)(arguments);
	} catch (std::out_of_range const&) {
		commandMap.at(shortToLongNameMapping.at(commandName))(arguments);
	}
}

void CommandInterpreter::printInvalidCommandMessage(std::string const &command) const {
	std::cerr << "Invalid command '" << command << "'! Try command 'help'." << std::endl;
}

}	// namespace util
