# PROL16 Tools

![](https://github.com/creiterer/prol16-tools/workflows/CI/badge.svg)

This repository is a collection of various tools for the PROL16 architecture, written in C++.  
It contains 
* an assembler `prol16-as`, 
* a disassembler `prol16-dis`, 
* a virtual machine `prol16-vm`.

## License

[Mozilla Public License 2.0](https://choosealicense.com/licenses/mpl-2.0/). See [LICENSE](LICENSE).  
For license information of [ANTLR4](https://github.com/antlr/antlr4) see [ANTLR4 LICENSE](https://github.com/antlr/antlr4/blob/master/LICENSE.txt).

## How to Build

### Prerequisites

* [CMake](https://cmake.org/) >= 3.7
* [Ninja](https://ninja-build.org/)
* [Clang](https://clang.llvm.org/) 7
* Clang-Tidy 7
* JRE >= 8
* uuid-dev

### Building

At first, clone the repository into your desired working directory:

```
cd working-directory
git clone https://github.com/creiterer/prol16-tools.git
```

The PROL16 toolchain uses CMake as build system. To initialize the cmake build execute the `initBuild.sh` script.

```
bash prol16-tools/initBuild.sh
```

After that, you should have a `build_prol16-tools` build directory next to the `prol16-tools` source directory in your working directory (out-of-source build).

To finally build the PROL16 tools, change to the `build_prol16-tools` directory and execute `ninja`:

```
cd build_prol16-tools
ninja
```

Alternatively, you can execute ninja with a specific target (e.g. `ninja prol16-as`) to build a specific tool instead of all tools.  
The executables of the built tools can then be found under `build_prol16-tools/prol16-*/src/main/prol16-*` (e.g. `build_prol16-tools/prol16-as/src/main/prol16-as`).

### Testing

To additionally run the unit tests, execute `ctest` in the build directory:

```
cd build_prol16-tools
ctest --output-on-failure
```

## Usage

### Assembler - `prol16-as`
The PROL16 assembler has a simple command-line interface:

```
./prol16-as -h
PROL16 Assembler
Usage: ./prol16-as [-v|--verbose] [-l|--log-file LOG-FILE] PROL16_ASSEMBLY_FILE
```

To assemble some PROL16 assembly file `example.s` to a PROL16 executable file `example.p16` run:

```
./prol16-as example.s
```

Optionally, you can turn on verbose logging with the `-v|--verbose` flag. 
If verbose logging is enabled, it is also possible to specify a log file with the `-l|--log-file` option, which defaults to `prol16-as.log`.

### Disassembler - `prol16-dis`
The PROL16 disassembler also provides a simple command-line interface:

```
/prol16-dis -h
PROL16 Disassembler
Usage: ./prol16-dis [-c|--console] PROL16_EXE_FILE
```

To disassemble some PROL16 executable file `example.p16` to a PROL16 assembly file `example.s` run:

```
./prol16-dis example.p16
```

Optionally, you can write the assembly output to the console with the `-c|--console` flag.


### Virtual Machine - `prol16-vm`
The PROL16 virtual machine provides the following command-line interface:

```
./prol16-vm -h
PROL16 Virtual Machine
Usage: ./prol16-vm [-d|--decimal] [-v|--verbose] [-l|--log-file LOG-FILE] [-i|--interactive] PROL16_EXE_FILE
```

To simply execute a PROL16 executable `example.p16` run:

```
./prol16-vm example.p16
```

To print numbers in decimal format, use the `-d|--decimal` flag.  
To enable verbose logging, use the `-v|--verbose` flag. To optionally specify a dedicated log file, use the `-l|--log-file` option, which defaults to `prol16-vm.log`.

The virtual machine also provides a simple interactive mode that can, among other things, be used for debugging. 
To enter the interactive mode, use the `-i|--interactive` flag:

```
./prol16-vm -i example.p16
pc=0x00000000|ra=0xDEAD|sp=0xFFFF|fp=0xFFFF|z=?|c=?: dec rsp             (rsp=0xFFFF)
> h
n|next [CONTINUE_COUNT] -- execute the next (CONTINUE_COUNT, default 1) instruction(s)
f|frame -- show the current stack frame
h|help -- show help
m|memory ADDRESS | ADDRESS_RANGE -- print memory of the given address (range)
q|quit 
s|stack -- show the current stack
r|register REG_NUMBER -- print the given register
> 
```

In interactive mode, the VM shows the state of the special registers and flags, the next instruction to be executed (`dec rsp` in the above example), and the register values with which the instruction is going to be executed. Then, the VM waits for some command.
