/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Unit test of the VirtualMemory class.
 */

#include "VirtualMemory.h"

#include "MemoryUtils.h"

#include <stdexcept>

#include "gtest/gtest.h"

using namespace PROL16;

namespace {
	bool isEmpty(VirtualMemory const &memory) {
		for (size_t address = 0; address < memory.size(); ++address) {
			if (memory[address] != VirtualMemory::MagicInitValue) {
				return false;
			}
		}

		return true;
	}

	bool contains(VirtualMemory const &memory, VirtualMemory::MemoryRange const &content) {
		size_t address = 0;

		// check that memory starts with content
		for (; address < content.size(); ++address) {
			if (memory[address] != content[address]) {
				return false;
			}
		}

		// check that remaining memory is still untouched
		for (; address < memory.size(); ++address) {
			if (memory[address] != VirtualMemory::MagicInitValue) {
				return false;
			}
		}

		return true;
	}
}

TEST(VirtualMemoryTest, testInitializationFromEmptyFile) {
	VirtualMemory memory;
	memory.initializeFromFile("resources/empty.p16");

	ASSERT_EQ(0, memory.getCodeSegmentSize());
	ASSERT_PRED1(isEmpty, memory);
}

TEST(VirtualMemoryTest, testInitializationFromFileWithOneInstruction) {
	VirtualMemory memory;
	memory.initializeFromFile("resources/single_instruction.p16");

	std::vector<VirtualMemory::Data> content = {0x0400};

	ASSERT_EQ(1, memory.getCodeSegmentSize());
	ASSERT_PRED2(contains, memory, content);
}

TEST(VirtualMemoryTest, testInitializationFromFileWithMultipleInstructions) {
	VirtualMemory memory;
	memory.initializeFromFile("resources/multiple_instructions.p16");

	std::vector<VirtualMemory::Data> content = {
			0x0000,
			0x0400,
			0x0800,
			0x8080,
			0x0c20,
			0x1020,
			0x3020,
			0x2000,
			0x2800,
			0x2c00,
			0x4020,
			0x4420,
			0x4820,
			0x4c20,
			0x5020,
			0x5420,
			0x5820,
			0x5c20,
			0x6020,
			0x6820,
			0x6c20,
			0x7020,
			0x7420,
			0x7820,
			0x7c20,
			0x0dee
	};

	ASSERT_EQ(content.size(), memory.getCodeSegmentSize());
	ASSERT_PRED2(contains, memory, content);
}

TEST(VirtualMemoryTest, testInitializationFromFileWithIncompleteInstruction) {
	VirtualMemory memory;
	ASSERT_THROW(memory.initializeFromFile("resources/incomplete_instruction.p16"), std::runtime_error);
}

TEST(VirtualMemoryTest, testReading) {
	PROL16::util::CodeSegment::Segment segment{
			0x0000,	// 0000
			0x0400,	// 0001
			0x0800, // 0002
			0x8080,	// 0003
			0x0c20,	// 0004
			0x1020,	// 0005
			0x3020,	// 0006
			0x2000,	// 0007
			0x2800,	// 0008
			0x2c00,	// 0009
			0x4020,	// 000A
			0x4420,	// 000B
			0x4820,	// 000C
			0x4c20,	// 000D
			0x5020,	// 000E
			0x5420,	// 000F
			0x5820,	// 0010
			0x5c20,	// 0011
			0x6020,	// 0012
			0x6820,	// 0013
			0x6c20,	// 0014
			0x7020,	// 0015
			0x7420,	// 0016
			0x7820,	// 0017
			0x7c20,	// 0018
			0x0dee	// 0019
	};

	VirtualMemory memory;
	memory.initializeCodeSegment(PROL16::util::CodeSegment(segment));

	ASSERT_EQ(0x0000, memory.read(0x0000));
	ASSERT_EQ(0x0dee, memory.read(0x0019));

	VirtualMemory::MemoryRange memoryRange = memory.readRange(0x0000, 0x0000);
	VirtualMemory::MemoryRange expectedRange{0x0000};
	ASSERT_EQ(1, memoryRange.size());
	ASSERT_EQ(expectedRange, memoryRange);

	memoryRange = memory.readRange(0x0000, 0x0003);
	expectedRange = {0x0000, 0x0400, 0x0800, 0x8080};
	ASSERT_EQ(4, memoryRange.size());
	ASSERT_EQ(expectedRange, memoryRange);

	memoryRange = memory.readRange(0x0016, 0x0019);
	expectedRange = {0x7420, 0x7820, 0x7c20, 0x0dee};
	ASSERT_EQ(4, memoryRange.size());
	ASSERT_EQ(expectedRange, memoryRange);

	ASSERT_EQ(segment, memory.readRange(0x0000, 0x0019));

	ASSERT_TRUE(memory.isCodeAddressValid(0x0000));
	ASSERT_TRUE(memory.isCodeAddressValid(0x0019));
	ASSERT_FALSE(memory.isCodeAddressValid(0x0020));
	ASSERT_FALSE(memory.isCodeAddressValid(PROL16::util::memory::InvalidCodeAddress));

	// does not throw because it is not out of the size of the memory
	// -> it "just" reads an invalid value
//	ASSERT_THROW(memory.read(0x0020), std::out_of_range);
//	ASSERT_THROW(memory.readRange(0x0020, 0x0010), std::out_of_range);
//	ASSERT_THROW(memory.readRange(0x0010, 0x0020), std::out_of_range);
//	ASSERT_THROW(memory.readRange(0x0020, 0x0020), std::out_of_range);
}

TEST(VirtualMemoryTest, testMemcpy) {
	PROL16::util::CodeSegment::Segment segment{
			0x0000,	// 0000
			0x0400,	// 0001
			0x0800, // 0002
			0x8080,	// 0003
			0x0c20,	// 0004
			0x1020,	// 0005
			0x3020,	// 0006
			0x2000,	// 0007
			0x2800,	// 0008
			0x2c00,	// 0009
			0x4020,	// 000A
			0x4420,	// 000B
			0x4820,	// 000C
			0x4c20,	// 000D
			0x5020,	// 000E
			0x5420,	// 000F
			0x5820,	// 0010
			0x5c20,	// 0011
			0x6020,	// 0012
			0x6820,	// 0013
			0x6c20,	// 0014
			0x7020,	// 0015
			0x7420,	// 0016
			0x7820,	// 0017
			0x7c20,	// 0018
			0x0dee	// 0019
	};

	VirtualMemory memory;
	memory.initializeCodeSegment(PROL16::util::CodeSegment(segment));

	memory.memcpy(0x0010, 0x0005, 10);

	VirtualMemory::MemoryRange destinationRange = memory.readRange(0x0010, 0x0014);
	VirtualMemory::MemoryRange sourceRange = memory.readRange(0x0005, 0x0009);
	VirtualMemory::MemoryRange expectedRange{
		0x1020,	// 0005
		0x3020,	// 0006
		0x2000,	// 0007
		0x2800,	// 0008
		0x2c00,	// 0009
	};

	ASSERT_EQ(expectedRange, destinationRange);
	ASSERT_EQ(sourceRange, destinationRange);
}
