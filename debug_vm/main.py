from time import sleep
from prompt_toolkit import prompt, HTML
from prompt_toolkit.key_binding import KeyBindings
from prompt_toolkit.patch_stdout import patch_stdout
from prompt_toolkit.shortcuts import ProgressBar

from declare_c_struct import Vm
import ctypes
from pathlib import Path
import subprocess
import sys


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

    except Exception as e:
        print("ERROR: Failed to get dylib, reason:", e)
        exit()

class Corewar:
    def __init__(self):
        # get my c function lib
        self.vm_lib = get_vm_lib()
        self.count = 0
        self.vm = Vm()
        self.p_vm = ctypes.pointer(self.vm)

    def loop(self, stop):
        while self.vm.cursor_nb:
            while self.vm.delta_cycle_counter < self.vm.cycle_to_die:
                if self.vm.cycle_total >= stop :
                    # vm_lib.dump_mem(self.vm.arena)
                    # print('cycle at: ', self.vm.cycle_total)
                    # print('cycle_to_die:', self.vm.cycle_to_die)
                    print('processus_nb: ', self.vm.cursor_nb)
                    print('live_nb between check: ', self.vm.live_counter, '\n\n')

                if self.vm_lib.one_round(self.p_vm) == False:
                    return
            self.vm_lib.check(self.p_vm)
        self.vm_lib.declare_winner(self.p_vm)


    def step(self, stop=1):
        # TODO: call C here...
        # should pass the steps argument to the C function to avoid
        # Python overhead on the loop
        if len(sys.argv) < 2:
            self.vm_lib.usage()
            sys.exit()
        else:
            self.vm_lib.init_vm(self.p_vm)

            # convert sys.argv to c type argv
            LP_c_char = ctypes.POINTER(ctypes.c_char)
            LP_LP_c_char = ctypes.POINTER(LP_c_char)
            argc = len(sys.argv)
            argv = (LP_c_char * (argc + 1))()
            for i, arg in enumerate(sys.argv):
                enc_arg = arg.encode("utf-8")
                argv[i] = ctypes.create_string_buffer(enc_arg)

            if self.vm_lib.parse(self.p_vm, argc, argv) and self.vm_lib.init_cursor_lst(self.p_vm):
                self.vm_lib.player_to_arena(self.p_vm)
                self.loop(stop)

            self.vm_lib.free_vm(self.p_vm)

        self.count += stop
        return

    def dump_memory(self):
        # TODO: call C here...
        print('cycle at: ', self.vm.cycle_total)
        print('cycle_to_die:', self.vm.cycle_to_die)
        print('processus_nb: ', self.vm.cursor_nb)
        print('live_nb between check: ', self.vm.live_counter, '\n\n')
        return {
            "count": self.count,
        }

def run(corewar):
    kb = KeyBindings()
    key_pressed = set()
    speed = 1

    @kb.add('x')
    def _(event):
        key_pressed.add('x')

    @kb.add('p')
    def _(event):
        key_pressed.add('p')

    bottom_toolbar = HTML(
        ' <b>[x]</b> Stop <b>[left]</b> Slower <b>[right]</b> Faster.'
    )

    def runner_generator():
        while True:
            corewar.step(stop=speed)
            yield corewar.dump_memory()['count']

    # TODO: should use a `prompt_toolkit.Application` instead to
    # display nice memory view
    with ProgressBar(key_bindings=kb, bottom_toolbar=bottom_toolbar) as pb:
        for memory in pb(runner_generator()):
            # TODO: display memory
            print("print memory :", memory)
            if 'x' in key_pressed:
                break
            if 'left' in key_pressed:
                speed /= 10
                speed = 1 if speed < 0 else speed
                break
            if 'right' in key_pressed:
                speed *= 10
                speed = 1000 if speed > 1000 else speed
                break
            key_pressed.clear()
            sleep(0.01)


def main():
    corewar = Corewar()

    with patch_stdout():
        while True:
            cmd = prompt('>>> ')
            if cmd == 'n':
                print('Reset vm state')
                vm = VM()
            elif cmd == 'r':
                run(corewar)
            elif cmd == "q":
                print('bye ;)')
                return
            else:
                print("usage:\n"
                    "\tn: reset vm\n"
                    "\tr: run vm\n"
                    "\tq: quit\n"
                )


if __name__ == '__main__':
    main()
