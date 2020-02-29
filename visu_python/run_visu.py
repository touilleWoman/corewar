import ctypes
import arcade
import binascii

import sys
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
BLUE = (0, 0, 128)
RED = (245, 78, 66)
GREY = (135, 133, 132)

SCREEN_X = 1200
SCREEN_Y = 900
CAPTION = "Corewar"
MEM_SIZE = 4*1024

ROW_COUNT = 64
COLUMN_COUNT = 15

WIDTH = 30
HEIGHT = 30

MARGIN = 5

SCREEN_WIDTH = (WIDTH + MARGIN) * COLUMN_COUNT + MARGIN
SCREEN_HEIGHT = (HEIGHT + MARGIN) * ROW_COUNT + MARGIN
SCREEN_TITLE = "Corewar"

class Visu(arcade.Window):








def run_visu(p_vm, C_lib, vm):
    pygame.init()
    pygame.display.set_caption('Corewar')
    visu = Visu(vm)
    while vm.cursor_nb :
        while vm.delta_cycle_counter < vm.cycle_to_die:
            visu.update()
            if C_lib.one_round(p_vm) == False or visu.done:
                pygame.quit()
                return ;
        C_lib.check(p_vm)
    C_lib.declare_winner(p_vm)
