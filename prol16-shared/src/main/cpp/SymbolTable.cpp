/**
 * @author		creiterer
 * @date 		2019-10-07
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "SymbolTable.h"

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

SymbolTable::Address SymbolTable::getSymbolAddress(std::string const &symbolName) const {
	auto found = std::find_if(symbolMap.cbegin(), symbolMap.cend(), [symbolName](SymbolMap::value_type const &value){
		return value.second.first == symbolName;
	});

	if (found == symbolMap.cend()) {
		throw std::out_of_range(::util::format("symbol '%s' is not in the symbol table", symbolName.c_str()));
	}

	return found->first;
}

SymbolTable::SymbolTable(SymbolMap symbolMap) : symbolMap(std::move(symbolMap)) {

}

}	// namespace util
}	// namespace PROL16
