#include "VirtualMachine.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "IVirtualDevice.h"

VirtualMachine::VirtualMachine(std::string const& fileName, size_t regCount) : mInstructionMemory(nullptr), mRegCount(regCount), mPc(0) {
	std::ifstream ifs(fileName, std::ios::binary | std::ios::ate);
	if (!ifs.is_open()) {
		std::cerr << "Could not open file: " << fileName << std::endl;
		return;
	}
	std::streamoff fileByteCount = ifs.tellg();
	if ((fileByteCount & 1) != 0) {
		std::cerr << "Invalid binary" << std::endl;
		return;
	}
	mInstructionSize = static_cast<size_t>(fileByteCount / Prol16::cDataIncrement);
	ifs.seekg(0, std::ios::beg);
	mInstructionMemory = new Prol16::TInstruction[mInstructionSize];
	ifs.read(reinterpret_cast<char*>(mInstructionMemory), fileByteCount);
	ifs.close();

	for (size_t i = 0; i < Prol16::cRegCount; ++i) {
		mRegisterFileWritten[i] = false;
	}
	mZeroFlagWritten = false;
	mCarryFlagWritten = false;
}

VirtualMachine::~VirtualMachine() {
	delete[] mInstructionMemory;
}

bool VirtualMachine::is_ready() const {
	return mInstructionMemory != nullptr;
}

bool VirtualMachine::RegisterDevice(IVirtualDevice* device, Prol16::TAddress begin, Prol16::TAddress end) {
	TVirtualDeviceInsertResult result = mVirtualDeviceMap.insert(TVirtualDeviceMap::value_type(AddressRange(begin, end), device));
	assert(result.second);
	return result.second;
}

void VirtualMachine::PrintWarning(std::string const& message) {
	std::cerr << "warning at pc 0x" << std::setfill('0') << std::setw(4) << std::hex << mPc << ": "
		<< message << std::endl;
}

Prol16::TData VirtualMachine::ReadRegisterFile(size_t idx) {
	if (idx >= mRegCount) {
		std::ostringstream oss;
		oss << "using higher register index than allowed index " << (mRegCount - 1);
		PrintWarning(oss.str());
	}
	if (!mRegisterFileWritten[idx]) {
		std::ostringstream oss;
		oss << "register index " << idx << " has not been used jet and has undefined value";
		PrintWarning(oss.str());
	}
	return mRegisterFile[idx];
}

void VirtualMachine::WriteRegisterFile(size_t idx, Prol16::TData const& data) {
	if (idx >= mRegCount) {
		std::ostringstream oss;
		oss << "using higher register index than allowed index " << (mRegCount - 1);
		PrintWarning(oss.str());
	}
	mRegisterFile[idx] = data;
	mRegisterFileWritten[idx] = true;
}

VirtualMachine::TVirtualDeviceMap::iterator VirtualMachine::GetVirtualDevice(Prol16::TAddress address) {
	TVirtualDeviceMap::iterator iter = mVirtualDeviceMap.lower_bound(AddressRange(address, address));
	if (iter == mVirtualDeviceMap.end() || address < iter->first.Begin() || address > iter->first.End()) {
		return mVirtualDeviceMap.end();
	}
	return iter;
}

Prol16::TData VirtualMachine::ReadMemory(Prol16::TAddress address) {
	TVirtualDeviceMap::iterator iter = GetVirtualDevice(address);
	if (iter == mVirtualDeviceMap.end()) {
		std::ostringstream oss;
		oss << "read from undefined memory address 0x" << std::setfill('0') << std::setw(4) << std::hex << address;
		PrintWarning(oss.str());
		return 0;
	}
	return iter->second->Read(address - iter->first.Begin());
}

void VirtualMachine::WriteMemory(Prol16::TAddress address, Prol16::TData const& data) {
	TVirtualDeviceMap::iterator iter = GetVirtualDevice(address);
	if (iter == mVirtualDeviceMap.end()) {
		std::ostringstream oss;
		oss << "write to undefined memory address 0x" << std::setfill('0') << std::setw(4) << std::hex << address;
		PrintWarning(oss.str());
		return;
	}
	iter->second->Write(address - iter->first.Begin(), data);
}

bool VirtualMachine::SetPc(Prol16::TAddress pc) {
	bool pcOutOfRange = pc >= mInstructionSize;
	if (pcOutOfRange) {
		PrintWarning("program counter went out of range, stopping virtual machine");
	} else {
		mPc = pc;
	}
	return !pcOutOfRange;
}

bool VirtualMachine::ReadZeroFlag() {
	if (!mZeroFlagWritten) {
		PrintWarning("zero flag has not been generated yet, undefined behavior");
	}
	return mZeroFlag;
}

bool VirtualMachine::ReadCarryFlag() {
	if (!mCarryFlagWritten) {
		PrintWarning("carry flag has not been generated yet, undefined behavior");
	}
	return mCarryFlag;
}

void VirtualMachine::WriteZeroFlag(bool zero) {
	mZeroFlag = zero;
	mZeroFlagWritten = true;
}

void VirtualMachine::WriteCarryFlag(bool carry) {
	mCarryFlag = carry;
	mCarryFlagWritten = true;
}

void VirtualMachine::Run() {
	while (mPc < mInstructionSize) {
		Prol16::TInstruction inst = mInstructionMemory[mPc];
		Prol16::TOpcode opcode = Prol16::MaskOpcode(inst);
		switch (opcode) {
			case Prol16::eNop:
				break;
			case Prol16::eSleep:
				std::cerr << "info at pc 0x" << std::setfill('0') << std::setw(4) << std::hex << mPc << ": sleep instruction reached, ending execution" << std::endl;
				return;
				break;
			case Prol16::eLoadi:
				if (!SetPc(mPc + 1)) return;
				WriteRegisterFile(Prol16::MaskRegRa(inst), mInstructionMemory[mPc]);
				break;
			case Prol16::eLoad:
				WriteRegisterFile(Prol16::MaskRegRa(inst), ReadMemory(ReadRegisterFile(Prol16::MaskRegRb(inst))));
				break;
			case Prol16::eStore:
				WriteMemory(ReadRegisterFile(Prol16::MaskRegRb(inst)), ReadRegisterFile(Prol16::MaskRegRa(inst)));
				break;
			case Prol16::eJump:
				if (!SetPc(ReadRegisterFile(Prol16::MaskRegRa(inst)))) return;
				break;
			case Prol16::eJumpc:
				if (ReadCarryFlag()) {
					if (!SetPc(ReadRegisterFile(Prol16::MaskRegRa(inst)))) return;
				} else {
					if (!SetPc(mPc + 1)) return;
				}
				break;
			case Prol16::eJumpz:
				if (ReadZeroFlag()) {
					if (!SetPc(ReadRegisterFile(Prol16::MaskRegRa(inst)))) return;
				} else {
					if (!SetPc(mPc + 1)) return;
				}
				break;
			case Prol16::eMove:
				WriteRegisterFile(Prol16::MaskRegRa(inst), ReadRegisterFile(Prol16::MaskRegRb(inst)));
				break;
			case Prol16::eAnd:
			{
				size_t raIdx = Prol16::MaskRegRa(inst);
				WriteCarryFlag(false);
				Prol16::TData result = ReadRegisterFile(raIdx) & ReadRegisterFile(Prol16::MaskRegRb(inst));
				WriteZeroFlag(result == 0);
				WriteRegisterFile(raIdx, result);
				break;
			}
			case Prol16::eOr:
			{
				size_t raIdx = Prol16::MaskRegRa(inst);
				WriteCarryFlag(false);
				Prol16::TData result = ReadRegisterFile(raIdx) | ReadRegisterFile(Prol16::MaskRegRb(inst));
				WriteZeroFlag(result == 0);
				WriteRegisterFile(raIdx, result);
				break;
			}
			case Prol16::eXor:
			{
				size_t raIdx = Prol16::MaskRegRa(inst);
				WriteCarryFlag(false);
				Prol16::TData result = ReadRegisterFile(raIdx) ^ ReadRegisterFile(Prol16::MaskRegRb(inst));
				WriteZeroFlag(result == 0);
				WriteRegisterFile(raIdx, result);
				break;
			}
			case Prol16::eNot:
			{
				size_t raIdx = Prol16::MaskRegRa(inst);
				WriteCarryFlag(false);
				Prol16::TData result = ~ReadRegisterFile(raIdx);
				WriteZeroFlag(result == 0);
				WriteRegisterFile(raIdx, result);
				break;
			}
			case Prol16::eAdd: {
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				Prol16::TData result = ra + ReadRegisterFile(Prol16::MaskRegRb(inst));
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag(result < ra);
				break;
			}
			case Prol16::eAddc: {
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				bool carry = ReadCarryFlag();
				Prol16::TData result = ra + ReadRegisterFile(Prol16::MaskRegRb(inst)) + (carry ? 1 : 0);
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag(result < ra || (carry && result <= ra));
				break;
			}
			case Prol16::eSub: {
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				Prol16::TData result = ra - ReadRegisterFile(Prol16::MaskRegRb(inst));
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag(result > ra);
				break;
			}
			case Prol16::eSubc: {
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				bool carry = ReadCarryFlag();
				Prol16::TData result = ra - ReadRegisterFile(Prol16::MaskRegRb(inst)) - (carry ? 1 : 0);
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag(result > ra || (carry && result >= ra));
				break;
			}
			case Prol16::eComp: {
				Prol16::TData ra = ReadRegisterFile(Prol16::MaskRegRa(inst));
				Prol16::TData result = ra - ReadRegisterFile(Prol16::MaskRegRb(inst));
				WriteZeroFlag(result == 0);
				WriteCarryFlag(result > ra);
				break;
			}
			case Prol16::eInc: {
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				Prol16::TData result = ra + 1;
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag(result < ra);
				break;
			}
			case Prol16::eDec: {
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				Prol16::TData result = ra - 1;
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag(result > ra);
				break;
			}
			case Prol16::eShl:
			{
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				Prol16::TData result = ra << 1;
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag((ra & 0x8000) != 0);
				break;
			}
			case Prol16::eShr:
			{
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				Prol16::TData result = ra >> 1;
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag((ra & 0x0001) != 0);
				break;
			}
			case Prol16::eShlc:
			{
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				Prol16::TData result = ra << 1 | (ReadCarryFlag() ? 0x0001 : 0);
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag((ra & 0x8000) != 0);
				break;
			}
			case Prol16::eShrc:
			{
				size_t raIdx = Prol16::MaskRegRa(inst);
				Prol16::TData ra = ReadRegisterFile(raIdx);
				Prol16::TData result = ra >> 1 | (ReadCarryFlag() ? 0x8000 : 0);
				WriteRegisterFile(raIdx, result);
				WriteZeroFlag(result == 0);
				WriteCarryFlag((ra & 0x0001) != 0);
				break;
			}
			case Prol16::ePrintInt:
				//wies
            //std::cout << "0x" << std::setfill('0') << std::setw(4) << std::hex << ReadRegisterFile(Prol16::MaskRegRa(inst)) << std::endl;
            std::cout << ReadRegisterFile(Prol16::MaskRegRa(inst)) << std::endl;
				break;
			default:
				PrintWarning("undefined opcode");
				break;
		}
		if (opcode != Prol16::eJump && opcode != Prol16::eJumpc && opcode != Prol16::eJumpz) {
			if (!SetPc(mPc + 1)) return;
		}
	}
}