import ctypes
import pygame
from pygame.locals import *
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





class Visu():
    def __init__(self, vm):
        self.done = False
        self.screen = pygame.display.set_mode((SCREEN_X , SCREEN_Y))
        self.screen = pygame.display.get_surface()
        # self.screen_rect = self.screen.get_rect()
        self.clock = pygame.time.Clock()
        self.fps = 60.0
        self.keys = pygame.key.get_pressed()
        self.vm = vm
        self.font = pygame.font.Font('freesansbold.ttf', 32)
        self.cube_size = (SCREEN_Y - 50) / 64

        # self.background = pygame.Surface(self.screen.get_size())
        # self.background = self.background.convert()
        # self.background.fill((250, 250, 250))

    def event(self):
        for event in pygame.event.get():
            self.keys = pygame.key.get_pressed()
            if event.type == QUIT or self.keys[pygame.K_ESCAPE]:
                self.done = True

    # def display_fps(self):
    #     caption = "{} - FPS: {:.2f}".format(CAPTION, self.clock.get_fps())
    #     pygame.display.set_caption(caption)


    def draw_font(self):
        # background = pygame.image.load("background.png").convert()
        # background = pygame.transform.scale(background, (SCREEN_X, SCREEN_Y))
        # self.screen.blit(background, (0, 0))
        if pygame.font:
            font = pygame.font.Font(None, 36)
            text = font.render("Informations", 1, (10, 10, 10))
            textpos = text.get_rect(centerx=self.background.get_width() / 2)
            self.background.blit(text, textpos)

    def draw_info_win(self):
        # win_surf = pygame.Surface(int(SCREEN_X / 4), int(SCREEN_Y - 200))
        win_surf = pygame.Surface(200, 200)
        win_surf.fill(WHITE)
        win_rect = win_surf.get_rect()
        self.screen.blit(win_surf, (100, 100))



    def prepare_sprites(self):
        sprite = Sprite(self.vm)
        allsprites = pygame.sprite.LayeredDirty(sprite)
        allsprites.clear(self.screen, self.background)
        return (allsprites)

    def draw_arena(self):
        data = binascii.hexlify(self.vm.arena, ' ')
        sys.exit
        cube_len = (SCREEN_Y - 50) / 64

        for x in range(0,64):
            for y in range(0,64):
                rec = (x * cube_len, cube_len * y + 25, cube_len, cube_len)
                pygame.draw.rect(self.screen, WHITE, rec, 1)





    def update(self):
        self.clock.tick(60)

        # allsprites = self.prepare_sprites()
        # text = self.font.render('cycle'+ str(self.vm.cycle_total), True, GREEN, blue)
        # textRect = text.get_rect()
        # textRect.center = (SCREEN_X / 2, SCREEN_Y / 2)
        # self.screen.blit(text, textRect)

        self.event()
        # allsprites.update()
        # rects = allsprites.draw(self.screen)
        self.draw_arena()
        pygame.display.update()
        # self.draw_info_win()
        # pygame.draw.rect(self.screen, GREEN, self.info_win)




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
