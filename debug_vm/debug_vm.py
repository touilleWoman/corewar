import sys
import subprocess
import ctypes
from pathlib import Path

from declare_c_struct import Vm


def get_C_lib():
    try:
        # make dylib
        base_dir = Path(__file__).parent.parent.absolute()
        vm_dir = base_dir / 'vm_dir'
        output = subprocess.run(['make', 'dylib', '-C', vm_dir])

        # open dylib to get all the C functions
        lib_path = vm_dir / 'C_lib.dylib'
        C_lib = ctypes.CDLL(str(lib_path))
        return (C_lib)

    except EXCEPTION as e:
        print("ERROR: Failed to get dylib, reason:", e)
        exit()


def run_vm(vm, p_vm, C_lib):
    while vm.cursor_nb:
        print(vm.cycle_total)
        while vm.delta_cycle_counter < vm.cycle_to_die:
            C_lib.one_round(p_vm)
    C_lib.declare_winner(p_vm)


def main():
    #get all my C functions for virtual machine
    C_lib = get_C_lib()

    if len(sys.argv) < 2:
        C_lib.usage()
    else:
        # vm is the main structure to be passed to C program
        vm = Vm()

        # create pointer of vm for C functions
        p_vm = ctypes.pointer(vm)

        C_lib.init_vm(p_vm)

        # convert sys.argv to c type argv
        LP_c_char = ctypes.POINTER(ctypes.c_char)
        LP_LP_c_char = ctypes.POINTER(LP_c_char)
        argc = len(sys.argv)
        argv = (LP_c_char * (argc + 1))()
        for i, arg in enumerate(sys.argv):
            enc_arg = arg.encode('utf-8')
            argv[i] = ctypes.create_string_buffer(enc_arg)

        if (C_lib.parse(p_vm, argc, argv) and C_lib.init_cursor_lst(p_vm)):
            C_lib.player_to_arena(p_vm)
            run_vm(vm, p_vm, C_lib)

        C_lib.free_vm(p_vm)


if __name__ == "__main__":
    main()
