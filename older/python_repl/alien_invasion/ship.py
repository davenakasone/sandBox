"""
all the game elements are treated as rectangles in pygame
some people may notice violations as of the physical world, but that is ok
this starts by taking 'self' and current instance of main class 'ai_game'

working with rectangle objects allows use of any of the 4 corner coordinates or the center to place object
(0,0) is the top left corner of the screen...or just use a combo 'midbottom' in this class
so your bottom right is (1200,800)
the coordinates refer to the game window, not the physical screen

this will handle continous motion by a flag (KEYUP vs KEYDOWN)

only integer portion of self.rect.x is stored in self.x, but that is good enough

update() modified to stop ship from leaving screen

we never make more than 1 ship...makes stats easy
"""
import pygame
from pygame.sprite import Sprite # to display lives

class Ship(Sprite):
    """ class to manage ship """
    def __init__(self, ai_game):
        """ initialize ship and set starting position """
        super().__init__()
        self.screen = ai_game.screen                    # makes it easy to access in all other methods
        self.settings = ai_game.settings                # created a settings attribute to use _update()
        self.screen_rect = ai_game.screen.get_rect()    # helps placement
        self.image = pygame.image.load('images/ship.bmp')   # load the image
        self.rect = self.image.get_rect()    # need to get rectangle attribute once it is loaded
        self.rect.midbottom = self.screen_rect.midbottom # match screens midbottom to place ship
        self.x = float(self.rect.x)        # attribute to store decimal of ship's coordinate
        self.moving_right = False                      # acts as flag for continous motion
        self.moving_left = False

    def update(self):
        """ updates ship's position from movement flags by x value, not rectangle
        seperate blocks...if both keys pressed, first one takes priority
        the bounds of screen are check before any movement """
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.x += self.settings.ship_speed
        if self.moving_left and self.rect.left > 0:
            self.x -= self.settings.ship_speed
        self.rect.x = self.x   # update rectangle obj w/ x var

    def blitme(self):
        """ draw ship at current location """
        self.screen.blit(self.image, self.rect) # draws ship at position specified by self.rect
    
    def center_ship(self):
        self.rect.midbottom = self.screen_rect.midbottom
        self.x = float(self.rect.x)
