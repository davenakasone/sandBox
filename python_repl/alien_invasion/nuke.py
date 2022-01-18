"""
I need to adjust this. I think the Sprite is messing it up, but using 'draw_bullet()' puts a band-aid on it
"""
import pygame
from pygame.sprite import Sprite

class Nuke(Sprite):
    """ a class to manage nukes fired from ship """
    def __init__(self, ai_game):
        """ creates a bullet object at ship's current position """
        super().__init__()
        self.screen = ai_game.screen
        self.settings = ai_game.settings
        self.color = self.settings.nuke_color
        # creates nuke rect @ (0,0) then moves
        self.rect = pygame.Rect(0, 0, self.settings.nuke_width, self.settings.nuke_height)
        self.rect.midbottom = ai_game.ship.rect.midbottom
        self.y = float(self.rect.y)    # store y coord as var
    
    def update(self):
        self.y -= self.settings.nuke_speed   # updates position of bullet
        self.rect.y = self.y                   # updates the rectangle
    
    def draw_bullet(self):
        pygame.draw.rect(self.screen, self.color, self.rect)
