import pygame
from pygame.sprite import Sprite

class Alien(Sprite):
    """ a class to represent a single alien in the fleet """

    def __init__(self, ai_game):
        """ initialize alien and set starting position """
        super().__init__()
        self.screen = ai_game.screen
        self.settings = ai_game.settings
        self.image = pygame.image.load('images/alien.bmp')
        self.rect = self.image.get_rect() # rect taken directly from image
        self.rect.x = self.rect.width   # starts aliens near top left
        self.rect.y = self.rect.height
        self.x = float(self.rect.x)     # stores alien's exact horizontal position
    
    def check_edges(self):
        """ returns True if alien is at edge of screen """
        #screen_rect = self.screen.get_rect()
        if self.rect.x >= self.settings.screen_width or self.rect.x <= 0:
            return True

    def update(self):
        """ moves aliens right or left"""
        self.x += (self.settings.alien_speed * self.settings.fleet_direction) # see how the numbers make sense 1, -1
        self.rect.x = self.x
        
