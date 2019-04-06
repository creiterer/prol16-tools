/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "VirtualMemory.h"

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

	bool contains(VirtualMemory const &memory, std::vector<VirtualMemory::Data> const &content) {
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
