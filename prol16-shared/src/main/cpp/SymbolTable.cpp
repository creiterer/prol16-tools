/**
 * @author		creiterer
 * @date 		2019-10-07
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing the symbol table of a PROL16 exe file.
 */

#include "SymbolTable.h"

#include "NumberUtils.h"
#include "StringUtils.h"

#include <algorithm>
#include <stdexcept>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace util {

SymbolTable SymbolTable::create(LabelTable const &labels, Address const stringsStartAddress) {
	SymbolMap symbolMap;
	Address nextStringAddress = stringsStartAddress;

	for (auto const &label : labels) {
		symbolMap.emplace(label.second, std::make_pair(label.first, nextStringAddress));
		nextStringAddress += memory::calcStringSpaceInMemory(label.first);
	}

	return SymbolTable(symbolMap);
}

SymbolTable SymbolTable::create(SymbolAddressTable const &symbolAddressTable, StringTable const &stringTable) {
	if (symbolAddressTable.size() != stringTable.size()) {
		throw std::runtime_error(::util::format("size of symbol address table (%hd) does not match size of string table (%hd)",
												symbolAddressTable.size(), stringTable.size()));
	}

	SymbolMap symbolMap;
	for (auto const &entry : symbolAddressTable) {
		symbolMap.emplace(entry.first, std::make_pair(stringTable.at(entry.second), entry.second));
	}

	return SymbolTable(symbolMap);
}

SymbolTable::Address SymbolTable::getSymbolAddress(std::string const &symbolName) const {
	auto found = std::find_if(symbolMap.cbegin(), symbolMap.cend(), [symbolName](SymbolMap::value_type const &value){
		return value.second.first == symbolName;
	});

	if (found == symbolMap.cend()) {
		throw std::out_of_range(::util::format("symbol '%s' is not in the symbol table", symbolName.c_str()));
	}

	return found->first;
}

SymbolTable::StringTable SymbolTable::getStringTable() const {
	StringTable stringTable;
	for (Entry const &entry : symbolMap) {
		stringTable.emplace(entry.second.second, entry.second.first);
	}

	return stringTable;
}

bool SymbolTable::contains(Address const symbolAddress) const {
	return symbolMap.count(symbolAddress) > 0;
}

bool SymbolTable::contains(std::string const &symbolName) const {
	auto found = std::find_if(symbolMap.cbegin(), symbolMap.cend(), [symbolName](SymbolMap::value_type const &value){
		return value.second.first == symbolName;
	});

	return found != symbolMap.cend();
}

void SymbolTable::logTo(::util::logging::Logger &logger) const {
	for (auto const &entry : symbolMap) {
		logger << ::util::formatAsHexNumberWithBase(entry.first) << " = " << entry.second.first << '\n';
	}
}

void SymbolTable::printTo(std::ostream &stream) const {
	for (auto const &entry : symbolMap) {
		stream << ::util::formatAsHexNumberWithBase(entry.first) << " = " << entry.second.first << '\n';
	}
}

SymbolTable::SymbolTable(SymbolMap symbolMap) : symbolMap(std::move(symbolMap)) {

}

}	// namespace util
}	// namespace PROL16
