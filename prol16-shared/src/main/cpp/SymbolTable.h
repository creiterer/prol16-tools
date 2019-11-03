/**
 * @author		creiterer
 * @date 		2019-10-07
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing the symbol table of a PROL16 exe file.
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SYMBOLTABLE_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SYMBOLTABLE_H_INCLUDED

#include "LabelUtils.h"
#include "Logger.h"
#include "MemoryUtils.h"

#include <map>
#include <string>
#include <unordered_map>
#include <utility>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

class SymbolTable final {
public:
	using Address = memory::Address;
	using SymbolMap = std::unordered_map<Address, std::pair<std::string, Address>>;
	using Entry = SymbolMap::value_type;
	using Size = SymbolMap::size_type;
	using iterator = SymbolMap::iterator;
	using const_iterator = SymbolMap::const_iterator;

	using SymbolAddressTable = std::unordered_map<Address, Address>;

	using StringTable = std::map<Address, std::string>;
	using StringTableEntry = StringTable::value_type;

	static SymbolTable create(LabelTable const &labels, Address const stringsStartAddress);
	static SymbolTable create(SymbolAddressTable const &symbolAddressTable, StringTable const &stringTable);

	SymbolTable() = default;

	inline std::string getSymbolName(Address const symbolAddress) const { return symbolMap.at(symbolAddress).first; }
	Address getSymbolAddress(std::string const &symbolName) const;

	StringTable getStringTable() const;

	bool contains(Address const symbolAddress) const;
	bool contains(std::string const &symbolName) const;

	inline Size size() const { return symbolMap.size(); }

	inline const_iterator begin() const noexcept { return symbolMap.begin(); }
	inline const_iterator cbegin() const noexcept { return symbolMap.cbegin(); }

	inline const_iterator end() const noexcept { return symbolMap.end(); }
	inline const_iterator cend() const noexcept { return symbolMap.cend(); }

	void logTo(::util::logging::Logger &logger) const;

private:
	SymbolMap symbolMap;

	explicit SymbolTable(SymbolMap symbolMap);
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SYMBOLTABLE_H_INCLUDED */
