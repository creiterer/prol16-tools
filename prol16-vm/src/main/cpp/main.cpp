#include <iostream>
#include <fstream>
#include <string>
#include "VirtualMachine.h"
#include "VirtualMemory.h"
#include "VirtualHmiDevice.h"

using std::cerr;
using std::endl;

static void printUsage(std::string const &errorMessage, std::string const &appName) {
	cerr << errorMessage << endl;
	cerr << "Usage: " << appName << " PROL16_EXE_FILE [number of registers]" << endl;
}

int main(int const argc, char const * const argv[]) {
	if (argc < 2 || argc > 3) {
		printUsage("Error: invalid number of arguments", argv[0]);
		return 1;
	}

	size_t numRegisters = Prol16::cRegCount;
	if (argc == 3) {
		numRegisters = std::stoi(argv[2]);
		if (numRegisters < 1 || numRegisters > Prol16::cRegCount) {
			std::cerr << "Register count must be between 1 and 32" << std::endl;
			return 3;
		}
	}
	VirtualMachine prol16vm(std::string(argv[1]), numRegisters);
	if (prol16vm.is_ready()) {
		// create 16384 words of memory, equals 32768 bytes
		VirtualMemory* virtualMemory = new VirtualMemory/*((1 << 15) / Prol16::cDataIncrement)*/;
		prol16vm.RegisterDevice(virtualMemory, 0x0000, 0x7fff);
		// regiser hmi device
		VirtualHmiDevice* hmiDevice = new VirtualHmiDevice();
		prol16vm.RegisterDevice(hmiDevice, 0x8000, 0x8000);
		prol16vm.Run();
		delete hmiDevice;
		delete virtualMemory;
	}

	return 0;
}
