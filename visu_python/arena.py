import pygame

SCREEN_X = 1200
SCREEN_Y = 900

WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
BLUE = (0, 0, 128)
RED = (245, 78, 66)
GREY = (135, 133, 132)

class Arena(pygame.sprite.DirtySprite):
    """docstring for Sprite"""
    def __init__(self, vm, visu):
        pygame.sprite.DirtySprite.__init__(self)
        # self.image, self.rect = pygame.load_image('sprite.png', -1)
        self.vm = vm
        self.visu = visu
        self.background = self.visu.screen.get_rect().left
        self.rects = []


    def init_rects(self):
        for x in range(5):
            self.rects.append(RED, [x * self.visu.cube_size, 100, ])
