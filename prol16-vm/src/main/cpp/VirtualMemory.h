/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_VIRTUAL_MEMORY_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_VIRTUAL_MEMORY_H_INCLUDED

#include "AddressUtils.h"
#include "NonCopyable.h"

#include <array>
#include <cstdint>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class VirtualMemory final : private ::util::NonCopyable {
public:
	using Data = uint16_t;
	using Address = PROL16::util::Address;

	static size_t const MemorySize = 1 << 16;	// 2^16 = 65536
	static Data const MagicInitValue = 0xCAFE;	// opcode = 0x32, ra = 23, rb = 30

	VirtualMemory();

	// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
	inline Data& operator[](Address const address) { return memory[address]; }

	// cppreference: If the value type is known to be a built-in type, the const variant should return by value.
	// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
	inline Data operator[](Address const address) const { return memory[address]; }

	// checked access
	inline Data read(Address const address) const { return memory.at(address); }
	inline void write(Address const address, Data const data) { memory.at(address) = data; }

	inline size_t size() const { return memory.size(); }
	inline size_t getCodeSegmentSize() const { return codeSegmentSize; }

	void initializeFromFile(std::string const &filename);

private:
	std::array<Data, MemorySize> memory{0};
	size_t codeSegmentSize{0};
};

}	// namespace PROL16

#endif
