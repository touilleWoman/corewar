from time import sleep
from prompt_toolkit import prompt, HTML
from prompt_toolkit.key_binding import KeyBindings
from prompt_toolkit.patch_stdout import patch_stdout
from prompt_toolkit.shortcuts import ProgressBar
import sys
import subprocess
import ctypes
from pathlib import Path

from .declare_c_struct import Vm


class Corewar:
    def __init__(self):
        # TODO: call C here...
        self.count = 0

    def step(self, steps=1):
        # TODO: call C here...
        # should pass the steps argument to the C function to avoid
        # Python overhead on the loop
        count += steps

    def dump_memory(self):
        # TODO: call C here...
        return {
            "count": self.count,
        }


def run_corewar(corewar):
    kb = KeyBindings()
    key_pressed = set()
    speed = 1

    @kb.add("x")
    def _(event):
        key_pressed.add("x")

    @kb.add("p")
    def _(event):
        key_pressed.add("p")

    bottom_toolbar = HTML(
        " <b>[x]</b> Stop <b>[left]</b> Slower <b>[right]</b> Faster."
    )

    def runner_generator():
        while True:
            corewar.step(steps=speed)
            x = corewar.dump_memory()
            x = x["count"]
            yield x

    # TODO: should use a `prompt_toolkit.Application` instead to
    # display nice memory view
    with ProgressBar(key_bindings=kb, bottom_toolbar=bottom_toolbar) as pb:
        for memory in pb(runner_generator()):
            # TODO: display memory
            if "x" in key_pressed:
                break
            if "left" in key_pressed:
                speed /= 10
                speed = 1 if speed < 0 else speed
                break
            if "right" in key_pressed:
                speed *= 10
                speed = 1000 if speed > 1000 else speed
                break
            key_pressed.clear()
            sleep(0.01)


def main():
    corewar = Corewar()

    with patch_stdout():
        while True:
            cmd = prompt(">>> ")
            if cmd == "n":
                print("Reset vm state")
                corewar = corewar()
            elif cmd == "r":
                run_corewar(corewar)
            elif cmd == "q":
                print("bye ;)")
                return
            else:
                print("usage:\n" "\tn: reset vm\n" "\tr: run vm\n" "\tq: quit\n")


if __name__ == "__main__":
    main()
