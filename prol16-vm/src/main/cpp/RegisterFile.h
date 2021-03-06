/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Class representing the PROL16 register file.
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_REGISTERFILE_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_REGISTERFILE_H_INCLUDED

#include "RegisterUtils.h"

#include <array>
#include <bitset>
#include <cstdint>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 {

class RegisterFile final {
public:
	using Data = uint16_t;
	using Register = util::Register;

	static Data const MagicInitValue = 0xDEAD;

	explicit RegisterFile(Data const initialStackPointerValue);

	Data& operator[](Register const reg);

	// cppreference: If the value type is known to be a built-in type, the const variant should return by value.
	Data operator[](Register const reg) const;

	inline size_t size() const { return registerFile.size(); }

	Data read(Register const reg) const;
	void write(Register const reg, Data const data);

	Data& getProgramCounter();
	Data readProgramCounter() const;
	void writeProgramCounter(Data const data);

	Data readReturnAddress() const;

	Data readStackPointer() const;
	void writeStackPointer(Data const data);

	Data readFramePointer() const;
	void writeFramePointer(Data const data);

private:
	std::array<Data, util::RegisterCount> registerFile{0};
};

}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_REGISTERFILE_H_INCLUDED */
