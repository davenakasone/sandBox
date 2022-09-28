"""
bullet inherits from Sprite (an import to pygame)
sprites let you group related elements in game and act on all grouped elements at one time
for a bullet instance/obj, __init__() takes current instance of game 'ai_game' and super() inherits from sprite
you do need some of your own attributes
the bullet initially depends on the ship's position

the bullets you fire are a big problem if you don't delete them because they will keep using memory
"""
import pygame
from pygame.sprite import Sprite

class Bullet(Sprite):
    """ a class to manage bullets fired from ship """
    def __init__(self, ai_game):
        """ creates a bullet object at ship's current position """
        super().__init__()
        self.screen = ai_game.screen
        self.settings = ai_game.settings
        self.color = self.settings.bullet_color
        # creates bullet rect @ (0,0) then moves
        self.rect = pygame.Rect(0, 0, self.settings.bullet_width, self.settings.bullet_height)
        self.rect.midtop = ai_game.ship.rect.midtop
        self.y = float(self.rect.y)    # store y coord as var
    
    def update(self):
        """ bullet can only move up the screen """
        self.y -= self.settings.bullet_speed   # updates position of bullet
        self.rect.y = self.y                   # updates the rectangle
    
    def draw_bullet(self):
        """ draws bullet to screen """
        pygame.draw.rect(self.screen, self.color, self.rect)
