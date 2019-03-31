#include "VirtualMemory.h"

// size ... number of words to allocate
VirtualMemory::VirtualMemory(/*size_t const size*/) : mMemory(new Prol16::TData[Prol16::cMemDataSize]) {
	
}

VirtualMemory::~VirtualMemory() {
	delete [] mMemory;
}

Prol16::TData VirtualMemory::Read(Prol16::TAddress const& address) {
	return *reinterpret_cast<Prol16::TData*>(&reinterpret_cast<Prol16::TByte*>(mMemory)[address]);
}

void VirtualMemory::Write(Prol16::TAddress const& address, Prol16::TData const& data) {
	*reinterpret_cast<Prol16::TData*>(&reinterpret_cast<Prol16::TByte*>(mMemory)[address]) = data;
}
