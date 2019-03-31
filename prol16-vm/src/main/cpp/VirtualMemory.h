#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include "Prol16.h"

#include "IVirtualDevice.h"

class VirtualMemory final : public IVirtualDevice {
public:
	VirtualMemory(/*size_t const size*/);
	virtual ~VirtualMemory();

	Prol16::TData Read(Prol16::TAddress const& address) override;
	void Write(Prol16::TAddress const& address, Prol16::TData const& data) override;

private:
	Prol16::TData* mMemory;
};

#endif
