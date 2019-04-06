/**
 * @author		creiterer
 * @date 		2019-04-05
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		brief description
 */

#ifndef PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_REGISTERFILE_H_INCLUDED
#define PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_REGISTERFILE_H_INCLUDED

#include <cstdint>
#include <array>
#include <bitset>

#include "RegisterUtils.h"

namespace PROL16 {

class RegisterFile final {
public:
	using Data = uint16_t;
	using Register = util::Register;

	static Data const MagicInitValue = 0xDEAD;

	RegisterFile();
	~RegisterFile() = default;

	Data& operator[](Register const reg);

	// cppreference: If the value type is known to be a built-in type, the const variant should return by value.
	Data operator[](Register const reg) const;

	inline size_t size() const { return registerFile.size(); }

	Data read(Register const reg) const;
	void write(Register const reg, Data const data);

private:
	std::array<Data, util::RegisterCount> registerFile;
};

}

#endif /* PROL16_TOOLS_PROL16_VM_SRC_MAIN_CPP_REGISTERFILE_H_INCLUDED */
