/**
 * @author		creiterer
 * @date 		2019-10-07
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SYMBOLTABLE_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SYMBOLTABLE_H_INCLUDED

#include "LabelUtils.h"
#include "MemoryUtils.h"

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

	static SymbolTable create(LabelTable const &labels, Address const stringsStartAddress);

	Address getSymbolAddress(std::string const &symbolName) const;

	inline Size size() const { return symbolMap.size(); }

	inline const_iterator begin() const noexcept { return symbolMap.begin(); }
	inline const_iterator cbegin() const noexcept { return symbolMap.cbegin(); }

	inline const_iterator end() const noexcept { return symbolMap.end(); }
	inline const_iterator cend() const noexcept { return symbolMap.cend(); }

private:
	SymbolMap const symbolMap;

	explicit SymbolTable(SymbolMap symbolMap);
};

}	// namespace util
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_SYMBOLTABLE_H_INCLUDED */
