/**
 * @author		creiterer
 * @date 		2019-09-13
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_COMMANDINTERPRETER_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_COMMANDINTERPRETER_H_INCLUDED

#include "NonCopyable.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace util {

class CommandInterpreter final : private ::util::NonCopyable {
public:
	using ArgumentVector = std::vector<std::string>;
	using CommandCallback = std::function<void(ArgumentVector const&)>;
	using ArgumentValidationFn = std::function<bool(std::string const&)>;

	explicit CommandInterpreter(std::string prompt);

	void registerCommand(std::string const &commandName,
						 unsigned const minArgCount, unsigned const maxArgCount,
						 std::string const &helpMessage, CommandCallback const &commandCallback,
						 ArgumentValidationFn const &argumentValidationFn = nullptr);

	void registerCommand(std::string const &shortCommandName, std::string const &longCommandName,
						 unsigned const minArgCount, unsigned const maxArgCount,
						 std::string const &helpMessage, CommandCallback const &commandCallback,
						 ArgumentValidationFn const &argumentValidationFn = nullptr);

	void registerContinueCommand(std::string const &shortCommandName, std::string const &longCommandName,
								 std::string const &helpMessage);

	void run();

	inline bool isQuit() const { return quit; }

private:
	using CommandMap = std::unordered_map<std::string, CommandCallback>;
	using StringMap = std::unordered_map<std::string, std::string>;
	using ArgumentCountRange = std::pair<unsigned, unsigned>;
	using ArgumentCountMap = std::unordered_map<std::string, ArgumentCountRange>;
	using ArgumentValidationFnMap = std::unordered_map<std::string, ArgumentValidationFn>;

	bool quit;
	bool cont;
	unsigned continueCount;
	unsigned invocationCount;
	std::string const prompt;
	CommandMap commandMap;
	StringMap helpMessageMap;
	StringMap shortToLongNameMapping;
	ArgumentCountMap argumentCountMap;
	ArgumentValidationFnMap argumentValidationFnMap;

	static void printInvalidCommandMessage(std::string const &command);
	static ArgumentVector parseCommand(std::string const &command);

	bool isCommandValid(std::string const &command) const;

	void showPrompt() const;
	std::string getCommand() const;
	void parseAndExecuteCommand(std::string const &command) const;
	std::string getCanonicalCommandName(std::string const &command) const;

	bool shouldContinue() const;
};

}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_COMMANDINTERPRETER_H_INCLUDED */
