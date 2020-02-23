import ctypes
import pygame

white = (255, 255, 255)
green = (0, 255, 0)
blue = (0, 0, 128)
x = 800
y = 600

def visu_loop(vm, screen, font):
    while True:
        screen.fill(white)
        for event in pygame.event.get():

            text = font.render('cycle'+ str(vm.cycle_total), True, green, blue)

            textRect = text.get_rect()
            textRect.center = (x / 2, y / 2)
            screen.blit(text, textRect)
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        pygame.display.update()


def run_visu(p_vm, Corewar, vm):

    pygame.init()

    screen = pygame.display.set_mode((x , y))

    pygame.display.set_caption('Corewar')

    font = pygame.font.Font('freesansbold.ttf', 32)
    while True:

    # Corewar.run_vm(p_vm)
