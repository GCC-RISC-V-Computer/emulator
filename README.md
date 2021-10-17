# Grove City College RISC V Computer Emulation Project
Project is being completed for ELEE 441 Computer Architecture.

Based on the Pineapple One project and used the following repositories as a starting point:
- [RISCie Program Template](https://github.com/32b-ttl-cpu/software)
- [Pineapple One Debugger](https://github.com/pineapple-one/debugger)

## Setup
### For the Debugger:

- Install Python and pip ```sudo apt install python3 python3-pip```
- Install project requirements ```python3 -m pip install -r requirements.txt```
- Change shell script permissions: ```chmod u+x *.sh```

### For compiling:
The toolchain for compiling programs will probably be later provided in a toolchain folder here, but for now you have to download it by yourself and change a few paths.

For more info about downloading the toolchain can be found here:
https://xpack.github.io/riscv-none-embed-gcc/install/


Relative paths are used where possible assuming that the toolchain was installed through xPacks and placed in ~/.local/xPacks/...

However, you must change the path in line 41 of dump.py to an absolute toolchain path 
(not sure why ~/ does not work).

To test everything you can open a terminal in the /program directory and enter "make". If no errors are shows and it generated your logisim file (PATH_LOGISIM_ROM), you can put it into logisim for a test (more in cpu-simulation). A dissasembled version can be found in build/app.lss and you can compare it to "EXAMPLE_DISSASEMBLY.lss" if you haven't made any changes.


WARNING:
I had to change the linker script to some generic one, as the one I was using may have been propriatory. This linker is very basic bare-bones one and maybe does not provide all the capabilities.
Also this CPU cannot read a program memory by the program itself, so anything that would normally go into .bss, etc will be unused at the moment. This is the reason why I declare the variable first and then assign it a value. I hope I find a fix soon.


## Running

Compile the program and run the debugger: ```./run.sh```

Run PineShell provided by the Pineapple One project: ```./runShell.sh```

  - At http://localhost:5000 is available our emulator
  - At http://localhost:5000/debugger is available our debugger
  
## Emulator

- To start emulator just click on Pineapple logo

## Troubleshooting
Some may need to reverse the makefile's addition of source files (assembly *.s and c files) so that compilation works. The important point it that the start label in the output APP.lss file is first.

## Tasks

- [ ] Finish input support by fully supporting ASCII to PS2 conversions in the debugger.
- [ ] Write our own get_keyboard_input method. An example assembly version is available in pineshell/APP.lss
- [ ] Write some RISC-V assembly
