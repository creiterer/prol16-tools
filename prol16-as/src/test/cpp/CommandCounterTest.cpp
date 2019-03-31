/**
 * @author		creiterer
 * @date 		2019-03-30
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#include "CommandCounter.h"

#include "gtest/gtest.h"

using namespace PROL16;

TEST(CommandCounterTest, testIncrement) {
	CommandCounter commandCounter;
	ASSERT_EQ(0, commandCounter.getNextInstructionAddress());

	++commandCounter;
	ASSERT_EQ(1, commandCounter.getNextInstructionAddress());

	CommandCounter oldCommandCounter = commandCounter++;
	ASSERT_EQ(2, commandCounter.getNextInstructionAddress());
	ASSERT_EQ(1, oldCommandCounter.getNextInstructionAddress());
}

TEST(CommandCounterTest, testBinaryOperator) {
	CommandCounter commandCounter;
	ASSERT_EQ(0, commandCounter.getNextInstructionAddress());

	commandCounter += 1;
	ASSERT_EQ(1, commandCounter.getNextInstructionAddress());

	commandCounter += 2;
	ASSERT_EQ(3, commandCounter.getNextInstructionAddress());

	commandCounter = commandCounter + 4;
	ASSERT_EQ(7, commandCounter.getNextInstructionAddress());
}
