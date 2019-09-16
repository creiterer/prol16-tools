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

	explicit CommandInterpreter(std::string prompt);

	void registerCommand(std::string const &commandName, std::string const &helpMessage,
						 CommandCallback const &commandCallback);

	void registerCommand(std::string const &shortCommandName, std::string const &longCommandName,
						 std::string const &helpMessage, CommandCallback const &commandCallback);

	void run() const;

	inline bool isQuit() const { return quit; }

private:
	using CommandMap = std::unordered_map<std::string, CommandCallback>;
	using StringMap = std::unordered_map<std::string, std::string>;

	bool quit;
	std::string const prompt;
	CommandMap commandMap;
	StringMap helpMessageMap;
	StringMap shortToLongNameMapping;

	bool isCommandValid(std::string const &command) const;

	void showPrompt() const;
	std::string getCommand() const;
	void parseAndExecuteCommand(std::string const &command) const;
	void printInvalidCommandMessage(std::string const &command) const;
};

}	// namespace util

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_COMMANDINTERPRETER_H_INCLUDED */
