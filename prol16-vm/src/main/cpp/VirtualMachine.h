#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <fstream>
#include <map>
#include <string>
#include "AddressRange.h"
#include "Prol16.h"

class IVirtualDevice;

class VirtualMachine final {
public:
	VirtualMachine(std::string const& fileName, size_t regCount);
	~VirtualMachine();
	bool is_ready() const;
	bool RegisterDevice(IVirtualDevice* device, Prol16::TAddress begin, Prol16::TAddress end);
	void Run();

private:
	typedef std::map<AddressRange, IVirtualDevice*> TVirtualDeviceMap;
	typedef std::pair<TVirtualDeviceMap::iterator, bool> TVirtualDeviceInsertResult;
	Prol16::TInstruction* mInstructionMemory;
	size_t mInstructionSize;
	TVirtualDeviceMap mVirtualDeviceMap;
	size_t const mRegCount;
	Prol16::TData mRegisterFile[Prol16::cRegCount];
	bool mRegisterFileWritten[Prol16::cRegCount];
	Prol16::TAddress mPc;
	bool mZeroFlag;
	bool mCarryFlag;
	bool mZeroFlagWritten;
	bool mCarryFlagWritten;
	void PrintWarning(std::string const& message);
	Prol16::TData ReadRegisterFile(size_t idx);
	void WriteRegisterFile(size_t idx, Prol16::TData const& data);
	TVirtualDeviceMap::iterator GetVirtualDevice(Prol16::TAddress address);
	Prol16::TData ReadMemory(Prol16::TAddress address);
	void WriteMemory(Prol16::TAddress address, Prol16::TData const& data);
	bool ReadZeroFlag();
	bool ReadCarryFlag();
	void WriteZeroFlag(bool zero);
	void WriteCarryFlag(bool carry);
	bool SetPc(Prol16::TAddress pc);
};

#endif
