#!/usr/bin/env python3
# extract machine code from objdump
# wykys 2019 MODIFIED!


import re
import argparse
import subprocess

if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='Parse machine code from elf files.'
    )

    parser.add_argument(
        '-i',
        '--input',
        dest='input',
        action='store',
        required=True,
        help='destination input elf file',
    )

    parser.add_argument(
        '-o',
        '--output',
        dest='output',
        action='store',
        default='out.mhc',
        help='destination output machine hex file',
    )

    parser.add_argument(
        '-d',
        '--dump',
        dest='objdump',
        action='store',
        #######################################
        # NEW toolchain:
        default='/home/(USERNAMEGOESHERE)/.local/xPacks/@xpack-dev-tools/riscv-none-embed-gcc/10.1.0-1.1.1/.content/bin/riscv-none-embed-objdump',
        #######################################
        # OLD toolchain:
        # default='/opt/8.2.0-2.1-20190425-1021/bin/riscv-none-embed-objdump',
        #######################################
        
        help='destination objdump',
    )

    parser.add_argument(
        '-p',
        '--print',
        dest='print',
        action='store_true',
        default=False,
        help='print',
    )

    input_path = parser.parse_args().input
    output_path = parser.parse_args().output
    objdump_path = parser.parse_args().objdump
    print_flag = parser.parse_args().print

    command = [
        objdump_path,
        input_path,
        '-dj',
        '.text',

    ]

    result = subprocess.run(
        command,
        stdout=subprocess.PIPE,
    ).stdout.decode('utf-8')

    regex = r'^\s*([0-9a-fA-F]+):\s+([0-9a-fA-F]+)\s+(.*)'
    match = [
        {
            'address': int(match.group(1), 16),
            'code': int(match.group(2), 16),
            'assembler': match.group(3)
        }
        for match in re.finditer(
            regex, result, re.MULTILINE
        )
    ]

    if print_flag:
        print(f'{"ADDRESS":7} \tMACHINE CODE\tASSEMBLER')
        print('-' * 80)
        for i in match:
            print(
                f'{i["address"]:07X}:\t{i["code"]:08X}\t{i["assembler"]}')

    with open(output_path, 'w') as fw:
        fw.write(''.join([f'{i["code"]:08X}\n' for i in match]))

    # entry_point = 'main'
    entry_point = '_start'
    regex = r'^\s*([0-9a-fA-F]+)\s' + f'<{entry_point}>:'
    main_address = int([match.group(1) for match in re.finditer(
        regex, result, re.MULTILINE)][0], 16)

    for i, m in enumerate(match):
        if m["address"] == main_address:
            print(f'start address is (HEX): {main_address:7X}')
            f = open("build/start_index.txt","w")
            f.write(str(i*4))
            f.close()
            print(f'start offset is (HEX): {i*4:7X}')
            break
