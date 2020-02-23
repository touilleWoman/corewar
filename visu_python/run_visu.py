import ctypes
import pygame

white = (255, 255, 255)
green = (0, 255, 0)
blue = (0, 0, 128)
x = 800
y = 600

def visu_update(vm, screen, font):
    screen.fill(white)
    text = font.render('cycle'+ str(vm.cycle_total), True, green, blue)
    textRect = text.get_rect()
    textRect.center = (x / 2, y / 2)
    screen.blit(text, textRect)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()

    pygame.display.update()


def run_visu(p_vm, C_lib, vm):

    pygame.init()

    screen = pygame.display.set_mode((x , y))

    pygame.display.set_caption('Corewar')

    font = pygame.font.Font('freesansbold.ttf', 32)

    while vm.cursor_nb:
        while vm.delta_cycle_counter < vm.cycle_to_die:
            visu_update(vm, screen, font)
            if C_lib.one_round(p_vm) == False:
                return
        C_lib.check(p_vm)
    C_lib.declar_winner(p_vm)
    # Corewar.run_vm(p_vm)
