import ctypes
import sys

MEM_SIZE = 4*1024
PROG_NAME_LENGTH = 128
COMMENT_LENGTH = 2048
CHAMP_MAX_SIZE = (MEM_SIZE / 6)
MAX_PLAYERS = 4
REG_NUMBER = 16

dy_path = './corewar.dylib'

Corewar = ctypes.cdll.LoadLibrary(dy_path)

class Bool(ctypes.Structure):
    _fields_ = [("bool", ctypes.c_int)
    ]        

class Cursor(ctypes.Structure):
    _fields_ = [("regs", ctypes.uint32 * (REG_NUMBER + 1)),
    ("live_counter",ctypes.c_uint),
    ("c_id", ctypes.c_uint),
    ("wait_cycle", ctypes.c_int),
    ("no_live_cycle", ctypes.c_int),
    ("pc", ctypes.int16),
    ("op", ctypes.uint8),
    (),
    (),

    ]
        

class Players(ctypes.Structure):
    """docstring for Players"""
    _fields_ = [("player_id",ctypes.c_uint8),
    (),
    (),
    (),
    (),

    ]
        

class Vm(ctypes.Structure)
    _fields_ = [("dump", ctypes.c_int),
                ("prog_name", ctypes.c_char * (PROG_NAME_LENGTH + 1)),

    ]



def main():
    if len(sys.argv) < 2:
        Corewar.usage()
    argc = ctypes.c_int(len(sys.argv))

    Corewar.main_c_for_python(agrc, argv)

if __name__ == "__main__":
    main()