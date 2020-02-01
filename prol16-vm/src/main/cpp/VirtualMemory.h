/**
 * @author		creiterer
 * @date 		2019-04-02
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing the PROL16 memory.
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_VIRTUAL_MEMORY_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_VIRTUAL_MEMORY_H_INCLUDED

#include "CodeSegment.h"
#include "MemoryUtils.h"
#include "NonCopyable.h"
#include "Prol16ExeFile.h"

#include <array>
#include <string>
#include <vector>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class VirtualMemory final : private ::util::NonCopyable {
public:
	using Data = PROL16::util::memory::Data;
	using Address = PROL16::util::memory::Address;

	static size_t const MemorySize = 1 << 16;	// 2^16 = 65536
	using Memory = std::array<Data, MemorySize>;

	using MemoryRange = std::vector<Data>;

	static constexpr Data MagicInitValue = 0xCAFE;	// opcode = 0x32, ra = 23, rb = 30

	static constexpr size_t CodeSegmentOffset = 0;
	static constexpr size_t MaxCodeSegmentSize = 0x8000;

	static constexpr size_t DataSegmentOffset = CodeSegmentOffset + MaxCodeSegmentSize;
	static constexpr size_t HeapStartAddress = DataSegmentOffset;
	static constexpr size_t StackStartAddress = 0xFFFF;		// starts at the very top of the memory and grows down

	VirtualMemory();

	// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
	inline Data& operator[](Address const address) { return memory[address]; }

	// cppreference: If the value type is known to be a built-in type, the const variant should return by value.
	// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
	inline Data operator[](Address const address) const { return memory[address]; }

	// checked access
	inline Data read(Address const address) const { return memory.at(address); }
	inline void write(Address const address, Data const data) { memory.at(address) = data; }

	std::string readString(Address const address) const;

	MemoryRange readRange(Address const startAddress, Address const endAddress) const;

	/**
	 *
	 * @param numBytes Number of 8-bit bytes to copy.
	 */
	void memcpy(Address const destination, Address const source, size_t const numBytes);

	/**
	 *
	 * @param numBytes Number of 8-bit bytes to increase the heap break.
	 * @return The prior heap break value.
	 */
	Address incrementHeapBreak(size_t const numBytes);

	inline size_t size() const noexcept { return memory.size(); }
	inline size_t getCodeSegmentSize() const noexcept { return codeSegmentSize; }
	inline bool isCodeAddressValid(Address const address) const noexcept { return address < getCodeSegmentSize(); }

	void initializeFromFile(std::string const &filename);
	void initializeCodeSegment(util::CodeSegment const &codeSegment);

private:
	Memory memory{0};
	size_t codeSegmentSize{0};
	Address heapBreak{HeapStartAddress};
};

}	// namespace PROL16

#endif
