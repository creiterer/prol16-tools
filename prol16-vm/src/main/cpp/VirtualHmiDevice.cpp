#include "VirtualHmiDevice.h"

#include <iostream>
#include <iomanip>

VirtualHmiDevice::VirtualHmiDevice() : m7SegHexData(0) {

}

Prol16::TData VirtualHmiDevice::Read(Prol16::TAddress const& address) {
	switch (address) {
	    case 0:
			return m7SegHexData;
		default:
			return 0;
	}
}

void VirtualHmiDevice::Write(Prol16::TAddress const& address, Prol16::TData const& data) {
	switch (address) {
		case 0:
			m7SegHexData = data;
			std::cout << "0x" << std::setfill('0') << std::setw(4) << std::hex << m7SegHexData << std::endl;
			break;
	}
}