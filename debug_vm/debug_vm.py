import sys
import subprocess
import ctypes
from pathlib import Path
from declare_c_struct import C_struct
from colorama import Fore


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


def user_input(stop, p_c_struct, vm_lib):
    u_input = input("-->")
    if u_input == "n":
        stop += 1
    elif u_input.isdigit() and int(u_input) > stop:
        stop = int(u_input)
    elif u_input == "q":
        vm_lib.free_vm(p_c_struct)
        exit()
    else:
        print("usage:\n" "\tn: next_cycle\n" "\tnb : go to cycle ...\n" "\tq: quit\n")
        user_input(stop, p_c_struct, vm_lib)
    return stop


def print_mem(arena):
    for i in range(0, 4096):
        if i % 32 == 0:
            print(Fore.GREEN + "0x%04x : " % i, end="")
        if (arena[i]) != 0:
            print(Fore.RED + "%02x" % (arena[i]), end=" ")
        else:
            print(Fore.WHITE + "%02x" % (arena[i]), end=" ")
        if (i + 1) % 32 == 0:
            print()


class Vm(object):
    """docstring for Vm"""

    def __init__(self):
        self.vm_lib = get_vm_lib()
        self.c_struct = C_struct()
        self.p_c_struct = ctypes.pointer(self.c_struct)

    def loop(self, stop=0):
        while self.c_struct.cursor_nb:
            while self.c_struct.delta_cycle_counter < self.c_struct.cycle_to_die:
                if self.c_struct.cycle_total >= stop:
                    print_mem(self.c_struct.arena)
                    print("cycle at: ", self.c_struct.cycle_total)
                    print("cycle_to_die:", self.c_struct.cycle_to_die)
                    print("processus_nb: ", self.c_struct.cursor_nb)
                    print("live_nb between check: ", self.c_struct.live_counter, "\n\n")
                    stop = user_input(stop, self.p_c_struct, self.vm_lib)

                if self.vm_lib.one_round(self.p_c_struct) == False:
                    return
            self.vm_lib.check(self.p_c_struct)
        self.vm_lib.declare_winner(self.p_c_struct)

    def run_vm(self):
        if len(sys.argv) < 2:
            self.vm_lib.usage()
        else:
            LP_c_char = ctypes.POINTER(ctypes.c_char)
            LP_LP_c_char = ctypes.POINTER(LP_c_char)
            self.vm_lib.init_vm(self.p_c_struct)
            argc = len(sys.argv)
            argv = (LP_c_char * (argc + 1))()
            for i, arg in enumerate(sys.argv):
                enc_arg = arg.encode("utf-8")
                argv[i] = ctypes.create_string_buffer(enc_arg)
            if self.vm_lib.parse(
                self.p_c_struct, argc, argv
            ) and self.vm_lib.init_cursor_lst(self.p_c_struct):
                self.vm_lib.player_to_arena(self.p_c_struct)
                self.loop()
            self.vm_lib.free_vm(self.p_c_struct)


def main():
    vm = Vm()
    vm.run_vm()


if __name__ == "__main__":
    main()
