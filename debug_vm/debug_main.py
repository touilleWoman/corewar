from time import sleep
from prompt_toolkit import prompt, HTML
from prompt_toolkit.key_binding import KeyBindings
from prompt_toolkit.patch_stdout import patch_stdout
from prompt_toolkit.shortcuts import ProgressBar
from prompt_toolkit import Application
from prompt_toolkit.layout.layout import Layout
from prompt_toolkit.buffer import Buffer
from prompt_toolkit.layout.containers import VSplit, Window
from prompt_toolkit.layout.controls import BufferControl, FormattedTextControl
from debug_vm import Vm

# class VM:
#     def __init__(self):
#         # TODO: call C here...
#         self.count = 0

#     def step(self, steps=1):
#         # TODO: call C here...
#         # should pass the steps argument to the C function to avoid
#         # Python overhead on the loop
#         self.count += steps
#         return

#     def dump_memory(self):
#         # TODO: call C here...
#         return {
#             "count": self.count,
#         }


def run(vm):
    buffer1 = Buffer()
    kb = KeyBindings()
    @kb.add("q")
    def exit_(event):
        event.app.exit()

    root_container = VSplit([
        # One window that holds the BufferControl with the default buffer on
        # the left.
        Window(content=BufferControl(buffer=buffer1)),

        # A vertical line in the middle. We explicitly specify the width, to
        # make sure that the layout engine will not try to divide the whole
        # width by three for all these windows. The window will simply fill its
        # content by repeating this character.
        Window(width=1, char='|'),

        # Display the text 'Hello world' on the right.
        Window(content=FormattedTextControl(text='Hello world')),
    ])

    layout = Layout(root_container)
    app = Application(layout=layout, full_screen=True, key_bindings=kb)
    app.run()
    # vm.run_vm()
    # key_pressed = set()
    # speed = 1

    # @kb.add("x")
    # def _(event):
    #     key_pressed.add("x")

    # @kb.add("p")
    # def _(event):
    #     key_pressed.add("p")

    # bottom_toolbar = HTML(
    #     " <b>[x]</b> Stop <b>[left]</b> Slower <b>[right]</b> Faster."
    # )

    # def runner_generator():
    #     while True:
    #         vm.step(steps=speed)
    #         yield vm.dump_memory()["count"]

    # # TODO: should use a `prompt_toolkit.Application` instead to
    # # display nice memory view
    # with ProgressBar(key_bindings=kb, bottom_toolbar=bottom_toolbar) as pb:
    #     for memory in pb(runner_generator()):
    #         # TODO: display memory
    #         if "x" in key_pressed:
    #             break
    #         if "left" in key_pressed:
    #             speed /= 10
    #             speed = 1 if speed < 0 else speed
    #             break
    #         if "right" in key_pressed:
    #             speed *= 10
    #             speed = 1000 if speed > 1000 else speed
    #             break
    #         key_pressed.clear()
    #         sleep(0.01)


def main():
    vm = Vm()

    with patch_stdout():
        while True:
            cmd = prompt(">>> ")
            if cmd == "n":
                print("Reset vm state")
                vm = VM()
            elif cmd == "r":
                run(vm)
            elif cmd == "q":
                print("bye ;)")
                return
            else:
                print("usage:\n" "\tn: reset vm\n" "\tr: run vm\n" "\tq: quit\n")


if __name__ == "__main__":
    main()
