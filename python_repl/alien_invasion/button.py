"""
pygame doesn't have a dedicated button feature, but use this class anytime you want to make a button
"""
import pygame.font

class Button:

    def __init__(self, ai_game, msg):
        self.screen = ai_game.screen
        self.screen_rect = self.screen.get_rect()

        self.width, self.height = 200, 50
        self.button_color = (0, 255, 255)
        self.text_color = (255, 255, 255)
        self.font = pygame.font.SysFont(None, 48) # None means use default font

        self.rect = pygame.Rect(0, 0, self.width, self.height)
        self.rect.center = self.screen_rect.center

        self._prep_msg(msg)
    
    def _prep_msg(self, msg):
        """ makes a rendered image out of msg and puts it on the button """
        self.msg_image = self.font.render(msg, True, self.text_color, self.button_color) #antialiasing makes more smooth (no background = trans)
        self.msg_image_rect = self.msg_image.get_rect() # center on button
        self.msg_image_rect.center = self.rect.center
    
    def draw_button(self):
        """ draws complete button on screen when called """
        self.screen.fill(self.button_color, self.rect)
        self.screen.blit(self.msg_image, self.msg_image_rect) # to draw text

