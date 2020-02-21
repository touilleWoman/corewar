import sys
import subprocess
import ctypes
from declare_c_struct import Vm
from pathlib import Path


def get_corewar_lib():
    try:
        # make dylib
        makefile_path = Path(__file__).parent.absolute()
        makefile_path = makefile_path / '..' / 'vm_dir'
        output = subprocess.run(['make', '-C', makefile_path])

        # open dylib to get all the C functions
        lib_path = Path(__file__).parent.absolute()
        lib_path = lib_path / '..' / 'vm_dir' / 'corewar.dylib'
        Corewar = ctypes.CDLL(str(lib_path))
        return (Corewar)

    except:
        print("ERROR: Failed to get dylib")
        exit()


def main():

    Corewar = get_corewar_lib()


    if len(sys.argv) < 2:
        Corewar.usage()
    else:
        # vm is the main structure to be given to C program
        vm = ctypes.pointer(Vm())
        Corewar.init_vm(vm)

        # convert sys.argv to argv for C program
        LP_c_char = ctypes.POINTER(ctypes.c_char)
        LP_LP_c_char = ctypes.POINTER(LP_c_char)
        argc = len(sys.argv)
        argv = (LP_c_char * (argc + 1))()
        for i, arg in enumerate(sys.argv):
            enc_arg = arg.encode('utf-8')
            argv[i] = ctypes.create_string_buffer(enc_arg)

        if (Corewar.parse(vm, argc, argv) and Corewar.init_cursor_lst(vm)):
            Corewar.player_to_arena(vm)
            Corewar.run_vm(vm)
        Corewar.free_vm(vm)


if __name__ == "__main__":
    main()
