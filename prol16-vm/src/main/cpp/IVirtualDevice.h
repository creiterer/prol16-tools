#ifndef I_VIRTUAL_DEVICE_H
#define I_VIRTUAL_DEVICE_H

#include "Prol16.h"

class IVirtualDevice {
public:
	virtual ~IVirtualDevice() = default;

	virtual Prol16::TData Read(Prol16::TAddress const& address) = 0;
	virtual void Write(Prol16::TAddress const& address, Prol16::TData const& data) = 0;
};

#endif
