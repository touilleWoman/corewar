"""
    t_vm (delclared in vm.h) is the main C structure for virtual machine.
    I use module "ctypes" to declare this structure in python,
    then pass it to C functions.
"""

import ctypes


MEM_SIZE = 4*1024
PROG_NAME_LENGTH = 128
COMMENT_LENGTH = 2048
CHAMP_MAX_SIZE = int(MEM_SIZE / 6)
MAX_PLAYERS = 4
REG_NUMBER = 16

# declare the c structure
class Bool(ctypes.Structure):
    _fields_ = [("bool", ctypes.c_int)]


class Cursor(ctypes.Structure):
    pass


class Cursor(ctypes.Structure):
    _fields_ = [("regs", ctypes.c_uint32 * (REG_NUMBER + 1)),
    ("live_counter",ctypes.c_uint),
    ("c_id", ctypes.c_uint),
    ("wait_cycle", ctypes.c_int),
    ("no_live_cycle", ctypes.c_int),
    ("pc", ctypes.c_int16),
    ("op", ctypes.c_uint8),
    ("carry", Bool),
    ("next", ctypes.POINTER(Cursor)),
    ("prev", ctypes.POINTER(Cursor))]


class Players(ctypes.Structure):
    _fields_ = [("prog_name", ctypes.c_char * (PROG_NAME_LENGTH + 1)),
    ("comment", (ctypes.c_char) * (COMMENT_LENGTH + 1)),
    ("prog_data", (ctypes.c_uint8) * (CHAMP_MAX_SIZE)),
    ("file_size", ctypes.c_uint),
    ("file", ctypes.POINTER(ctypes.c_uint8)),
    ("prog_size",ctypes.c_int),
    ("live_counter",ctypes.c_int),
    ("player_id",ctypes.c_int8)]


class Vm(ctypes.Structure):
    _fields_ = [("players", Players * MAX_PLAYERS),
    ("arena", ctypes.c_uint8 * MEM_SIZE),
    ("dump", ctypes.c_int),
    ("player_nb", ctypes.c_uint8),
    ("cycle_total", ctypes.c_int),
    ("cycle_to_die", ctypes.c_int),
    ("max_check_counter", ctypes.c_int),
    ("live_counter", ctypes.c_int),
    ("Cursor", ctypes.POINTER(Cursor)),
    ("cursor_nb", ctypes.c_int),
    ("winner", ctypes.c_int),
    ("flags", ctypes.c_char)]
