#!/usr/bin/env python3

import re
import sys
from pathlib import Path
import subprocess

PATH_ELF = 'build/APP.elf'
PATH_BIN_IN = 'build/APP.bin'
PATH_BIN_OUT = 'build/APP_edit.bin'
PATH_MHC = 'build/APP.mhc'

#######################################
# toolchain:
PATH_READELF='~/.local/xPacks/@xpack-dev-tools/riscv-none-embed-gcc/10.1.0-1.1.1/.content/bin/riscv-none-embed-readelf'
PATH_OBJDUMP='~/.local/xPacks/@xpack-dev-tools/riscv-none-embed-gcc/10.1.0-1.1.1/.content/bin/riscv-none-embed-objdump'
#######################################

def check_path(path: str) -> bool:
    if not Path(path).is_file():
        print(f'Error: {path} not exist', file=sys.stderr)
        exit(1)


def load_bin(path: str) -> list:
    check_path(path)
    with open(path, 'rb') as fr:
        raw = fr.read()

    data = []
    for i in range(0, len(raw), 4):
        tmp = raw[i]
        tmp |= raw[i+1] << 8
        tmp |= raw[i+2] << 16
        tmp |= raw[i+3] << 24
        data.append(tmp)

    return data


def save_bin(path: str, data: list) -> None:
    with open(path, 'wb') as fw:

        bytes = []
        for inst in data:
            for i in range(4):
                byte = (inst >> i*8) & 0xFF
                bytes.append( byte )
                            
        fw.write(bytearray(bytes))

def show_bin(data: list) -> None:
    for i, d in enumerate(data):
        addr = 0x08000000 + i*4
        print(f'{addr:08X}:  {d:08X}')
    else:
        print(i*4)

def gen_mhc(data: list) -> None:
    with open(PATH_MHC, 'w') as fw:
        for instructtuctin in data:
            fw.write(f'{instructtuctin:08X}\n')


def jump_to_start(data: list) -> list:
    command = [
        PATH_READELF,
        PATH_ELF,
        '-h'
    ]

    result = subprocess.run(
        command,
        stdout=subprocess.PIPE,
    ).stdout.decode('utf-8')

    start_address = int(result.split('\n')[10].split('Entry point address:')[1].strip(), 16) + 4
        
    INST_JMP = 0x0006F
    jmp = (start_address<<20) + INST_JMP

    return [jmp] + data

if __name__ == '__main__':
    
    app = load_bin(PATH_BIN_IN)
    
    #app = jump_to_start(app)
    #show_bin(app[1:])
    

    gen_mhc(app)

    save_bin(PATH_BIN_OUT, app)