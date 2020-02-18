# from ctypes import *
import ctypes
import sys

dy_path = './corewar.dylib'

Corewar = ctypes.cdll.LoadLibrary(dy_path)



def main():
    if len(sys.argv) < 2:
        Corewar.usage()
    argc = ctypes.c_int(len(sys.argv))

    Corewar.main_c_for_python(agrc, argv)


class Vm(ctypes.Structure)
    _fields_ = [("dump", ctypes.c_int),

    ]


if __name__ == "__main__":
    main()