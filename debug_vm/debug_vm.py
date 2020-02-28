import sys
import subprocess
import ctypes
from pathlib import Path
from declare_c_struct import Vm

def get_vm_lib():
    try:
        # make dylib
        base_dir = Path(__file__).parent.parent.absolute()
        vm_dir = base_dir / "vm_dir"
        output = subprocess.run(["make", "dylib", "-C", vm_dir])

        # open dylib to get all the C functions
        lib_path = vm_dir / "vm_lib.dylib"
        vm_lib = ctypes.CDLL(str(lib_path))
        return vm_lib

    except EXCEPTION as e:
        print("ERROR: Failed to get dylib, reason:", e)
        exit()


def user_input(stop, p_vm, vm_lib):
    u_input = input('type "n" for next cyle, or cycle nb, "exit" to quit -->')
    if u_input == 'n':
        stop += 1
    elif u_input.isdigit() and int(u_input) > stop:
        stop = int(u_input)
    elif u_input == "exit" :
        vm_lib.free_vm(p_vm)
        exit()
    else :
        print('wrong input')
        user_input(stop)
    return stop

def loop(vm, p_vm, vm_lib):
    stop = 0
    while vm.cursor_nb:
        while vm.delta_cycle_counter < vm.cycle_to_die:
            if vm.cycle_total >= stop :
                vm_lib.dump_mem(vm.arena)
                print('cycle at: ', vm.cycle_total)
                print('cycle_to_die:', vm.cycle_to_die)
                print('processus_nb: ', vm.cursor_nb)
                print('live_nb between check: ', vm.live_counter, '\n\n')
                stop = user_input(stop, p_vm, vm_lib)

            if vm_lib.one_round(p_vm) == False:
                return
        vm_lib.check(p_vm)
    vm_lib.declare_winner(p_vm)


def main_vm():
    # get all my C functions for virtual machine
    vm_lib = get_vm_lib()

    if len(sys.argv) < 2:
        vm_lib.usage()
    else:
        # vm is the equivalent main C structure
        vm = Vm()

        # create pointer of vm for C functions
        p_vm = ctypes.pointer(vm)

        vm_lib.init_vm(p_vm)

        # convert sys.argv to c type argv
        LP_c_char = ctypes.POINTER(ctypes.c_char)
        LP_LP_c_char = ctypes.POINTER(LP_c_char)
        argc = len(sys.argv)
        argv = (LP_c_char * (argc + 1))()
        for i, arg in enumerate(sys.argv):
            enc_arg = arg.encode("utf-8")
            argv[i] = ctypes.create_string_buffer(enc_arg)

        if vm_lib.parse(p_vm, argc, argv) and vm_lib.init_cursor_lst(p_vm):
            vm_lib.player_to_arena(p_vm)
            loop(vm, p_vm, vm_lib)

        vm_lib.free_vm(p_vm)


if __name__ == "__main__":
    main_vm()
