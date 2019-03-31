#ifndef VIRTUAL_HMI_DEVICE
#define VIRTUAL_HMI_DEVICE

#include "Prol16.h"

#include "IVirtualDevice.h"

class VirtualHmiDevice final : public IVirtualDevice {
public:
	VirtualHmiDevice();
	virtual ~VirtualHmiDevice() = default;

	Prol16::TData Read(Prol16::TAddress const& address) override;
	void Write(Prol16::TAddress const& address, Prol16::TData const& data) override;

private:
	Prol16::TData m7SegHexData;
};

#endif
