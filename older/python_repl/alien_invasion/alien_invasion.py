"""
this controls the main flow of the program
it will even start off the CLI when it runs as main()   see bottom
...this thing gets updated a lot

as it grew, refactoring was used, starting with run_game()
a helper method does work inside a class, but isn't supposed to be called through an instance
use a single leading underscore _helper()
most people find starting out writting is good, then they see the sections, then refactoring helps

whenever a key is pressed, pygame takes it as an event
each event is registered with pygame.event.get()
each key press is a KEYDOWN event, so see if it was a defined action key when this event happens
continuous moving vs incremental, do what is appropriate

now the problem is adjusting speed and when the ship goes out of screen range, everything is gone

going to refactor the _check_events() that was already refactored, into keyup and keydown ... 2 new helper methods
and 'q' to quit...if you are to lazy to x out of the window      make sure you have a quit ability before going full screen

pygame has a fullscreen mode you can use an abuse

when you use a for loop with a list or group, python expects the list to keep the same length as long as loop runs
here, we just loop over a copy of the group, allowing the actual list to be modified insinde the loop

the aliens are made one instance at a time. it is part of the setup
to build fleet, you need to know how many aliens can fit....get the spacing also

when any alien reaches an edge, the entire fleet must change direction and drop down

pygame has most of this planned..use sprite.groupcollide() to check for collisions between members of 2 groups
its important to check for collisions after the bullets are updated, but before the alien can move (keeps same point in time)
it will compare each bullet rectangle to each alien rectange and return a dictionary of what collided
make each key a bullet and each value the alien that needs to be registered as killed

check to see if aliens are all gone, then respawn a new fleet

adding a kill for aliens reaching bottom (lose a ship)
only giving 3 lives (ships), then game ends
spritecollideany() loops through group to check if any elements hit the sprite
if no collision, None is returned  (evaluates to False) if collision, returns colliding element
on the collision, you have to update a lot

the button has to be handeled so it does not react when it is not there
helps to hide cursor when game is active
"""

import sys
import pygame
import copy
from time import sleep    # pauses game on ship kill

from settings import Settings
from ship import Ship
from bullet import Bullet
from nuke import Nuke
from alien import Alien
from game_stats import GameStats
from button import Button
from scoreboard import Scoreboard


class AlienInvasion:
    """ main class to manage game assets and behaviors """

    def __init__(self):
        """ initialize the game, and create game resources """
        pygame.init()
        self.settings = Settings()  # keep all the settings in this attribute

        # for full screen (pick one)
        #self.screen = pygame.display.set_mode((0,0), pygame.FULLSCREEN)
        #self.settings.screen_width = self.screen.get_rect().width
        #self.settings.screen_height = self.screen.get_rect().height

        # not for full screen (pick one)
        self.screen = pygame.display.set_mode(
            (self.settings.screen_width, self.settings.screen_height))  # the surface is made
        
        pygame.display.set_caption("Alien Invasion")
        self.stats = GameStats(self) # instantiate an object to hold stats ...order is important here
        self.ship = Ship(self) # passing to tack on more attributes, instance of ship created, 'self' refers to current inst
        self.bullets = pygame.sprite.Group() # like a list, but with some nice features, holds all bullets fired
        self.nukes = pygame.sprite.Group()
        self.aliens = pygame.sprite.Group() # similar to bullets
        self._create_fleet()
        self.play_button = Button(self, "Play") # only need one play button, so put here   see update_screen()
        self.sb = Scoreboard(self)  # make a scoreboard ... order matters, won't compose if attributes not there

    def run_game(self):
        """Start the main loop for the game."""
        while True:
            self._check_events() # uses helper
            if self.stats.game_active: # only if player is still alive
                self.ship.update()  # update ship position before update screen and after checking keyboard
                self._update_bullets() # see helpers for details
                self._update_nukes() #""""""
                self._update_aliens()
            self._update_screen()
    
    def _check_events(self):
        """ watch for keyboard and mouse events """
        for event in pygame.event.get():
            if event.type == pygame.QUIT:   # checking to see if player closed window
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self._check_keydown_events(event)
            elif event.type == pygame.KEYUP:        #...so if you press R и L the ship should stay still
                 self._check_keyup_events(event)
            elif event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                self._check_play_button(mouse_pos) # happens on any click to screen, need to see coordinates now
    
    def _check_play_button(self, mouse_pos):
        """ starts a new game if button clicked """
        button_clicked = self.play_button.rect.collidepoint(mouse_pos) # needs to respond at a valid time
        if button_clicked and self.play_button.rect.collidepoint(mouse_pos):
            self.settings.initialize_dynamic_settings() # resets
            self.stats.reset_stats()
            self.stats.game_active = True
            self.sb.prep_score() # calling after stats reset takes the 0 default
            self.sb.prep_level() # to ensure level is set to 1
            self.sb.prep_ships()
            self.aliens.empty()
            self.bullets.empty()
            self.nukes.empty()
            self._create_fleet()
            self.ship.center_ship()
            pygame.mouse.set_visible(False) # hides cursor
    
    def _check_keydown_events(self, event):
        """ responds to key press if defined """
        if event.key == pygame.K_RIGHT:       #if elif is ok here because each even is connected to 1 key
            self.ship.moving_right = True
        elif event.key == pygame.K_LEFT:
            self.ship.moving_left = True
        elif event.key == pygame.K_q:
            sys.exit()
        elif event.key == pygame.K_SPACE:
            self._fire_bullet()
        elif event.key == pygame.K_n:
            self._fire_nuke()
        elif event.key == pygame.K_r:
            if self.settings.nuke_limit <= 0:
                self.settings.nuke_limit = 5   # get 5 more nukes by pressing reload
                print("5 more nukes added")

    def _check_keyup_events(self,event):
        """ responds to key realese if defined """
        if event.key == pygame.K_RIGHT:
            self.ship.moving_right = False
        elif event.key == pygame.K_LEFT:
            self.ship.moving_left = False

    def _fire_bullet(self):
        """ create a new bullet and add to the group """
        if len(self.bullets) < self.settings.bullets_allowed and self.settings.bullet_burst == False:
            new_bullet = Bullet(self)
            self.bullets.add(new_bullet)    # add method is specifically for groups in this case
        else:
            for num in range(self.settings.bullet_pulses):
                new_bullet = Bullet(self)
                new_bullet.y -= self.settings.bullet_height * num
                self.bullets.add(new_bullet)
    
    def _fire_nuke(self):
        if self.settings.nuke_limit > 0:
            new_nuke = Nuke(self)
            self.settings.nuke_limit -= 1
            print(self.settings.nuke_limit, "nukes remain") # for testing
            self.bullets.add(new_nuke)
                
    def _update_bullets(self):
        """ update position of bullets and get rid of old bullets """
        self.bullets.update() # need to update position of active bullets...update on group calls update on all elements
        #get rid of used/out-of-range bullets
        for bullet in self.bullets.copy():
            if bullet.rect.bottom <= 0:
                self.bullets.remove(bullet)
        #print(len(self.bullets)) # only for testing, take off or game will slow down
        self._check_bullet_alien_collisions()
    
    def _update_nukes(self):
        self.nukes.update()   # update entire group
        for nuke in self.nukes.copy():
            if nuke.rect.bottom <= 0:
                self.nukes.remove(nuke)
        self._check_nuke_alien_collisions() #""""""
    
    def _check_bullet_alien_collisions(self):
        """ a refactoring of update_bullets, just looks for collisions, moves hits, makes new alines (if all dead) """
        collisions = pygame.sprite.groupcollide(self.bullets, self.aliens, self.settings.bullet_pen, True) # check for collisions
        if collisions:
            for aliens in collisions.values():
                self.stats.score += self.settings.alien_points * len(aliens) # find all collisions
            self.sb.prep_score()
            self.sb.check_high_score()
        # says delete objects (bullets and aliens) that have collided...make a high powered bullet by turning False
        if not self.aliens: # if there are no more aliens
            self.bullets.empty() # clear screen of bullets
            self.nukes.empty()
            self._create_fleet() # make another fleet
            self.settings.increase_speed() # speeds increase when a fleet is cleared....level-up
            self.stats.level += 1
            self.sb.prep_level()
    
    def _check_nuke_alien_collisions(self):
        ccollisions = pygame.sprite.groupcollide(self.nukes, self.aliens, False, True)
        if ccollisions:
            for aliens in ccollisions.values():
                self.stats.score += self.settings.alien_points * len(aliens) # find all collisions
            self.sb.prep_score()
            self.sb.check_high_score()
        if not self.aliens:
            self.bullets.empty()
            self.nukes.empty()
            self._create_fleet()
            self.settings.increase_speed() # speeds increase when a fleet is cleared....level-up
            self.stats.level += 1
            self.sb.prep_level()

    def _update_aliens(self):
        """ updates position of all aliens in the fleet (that haven't been shot) """
        self._check_fleet_edges()
        self.aliens.update() # using the update method of Alien class, the sprite takes the group
        if pygame.sprite.spritecollideany(self.ship, self.aliens):   # ship is sprite, using ground of aliens, will stop for any
            #print("ship killed") # for testing
            self._ship_hit()
        self._check_aliens_bottom()  # reaching bottom also counts as a kill

    def _create_fleet(self):
        """ instance of alien class added to the group to hold fleet """
        dummy_alien = Alien(self) # this alien is just for measuring...probably will be a memory leak later
        alien_width, alien_height = copy.deepcopy(dummy_alien.rect.size)  # double assigment off tuple
        del dummy_alien # not if I can help it
        available_space_x = self.settings.screen_width - (2 * alien_width)   # leave a little at right and left edge
        number_aliens_x = available_space_x // (2 * alien_width) # floor divide to get quotient part of surface
        ship_height = self.ship.rect.height
        available_space_y = self.settings.screen_height - (3 * alien_height) - ship_height  # finds row space off vertical
        number_rows = available_space_y // (2 * alien_height)
        # now you can make the fleet
        for row_number in range(number_rows):
            for alien_number in range(number_aliens_x):
                self._create_alien(alien_number, row_number)

    def _create_alien(self, alien_number, row_number):
        """ creates an alien for the row """
        alien = Alien(self)
        alien_width, alien_height = alien.rect.size
        alien.x = alien_width + (2 * alien_width * alien_number)
        alien.rect.x = alien.x
        alien.rect.y = alien.rect.height + (2 * alien.rect.height * row_number)
        self.aliens.add(alien)
    
    def _check_fleet_edges(self):
        """ respond if any aliens have reached an edge """
        for alien in self.aliens.sprites():
            if alien.check_edges():
                self._change_fleet_direction()
                break
    
    def _change_fleet_direction(self):
        """ drop the entire fleet and change direction (if needed) """
        for alien in self.aliens.sprites():
            alien.rect.y += self.settings.fleet_drop_speed     # gets all of them to fall
        self.settings.fleet_direction *= -1     # slick way to alternate

    def _update_screen(self):
        """ updates images, flips to new screen """
        self.screen.fill(self.settings.bg_color) # redraw the screen during each pass through the loop
        self.ship.blitme() # important to call after filling background, now you can draw ship
        for bullet in self.bullets.sprites():   # this gets the group of objects and makes them call
            bullet.draw_bullet()
        self.aliens.draw(self.screen)
        self.sb.show_score() # draw the score   can use this to get messages
        if not self.stats.game_active: # only draw button when restart or initially  drawn last it stays on top
            self.play_button.draw_button()
        pygame.display.flip() # make the most recently drawn screen visible
    
    def _ship_hit(self):
        """ responds to ship being hit by alien """
        if self.stats.ships_left > 0: # have to have at least one life left to continue
            self.stats.ships_left -= 1 # decrement lives by 1
            self.sb.prep_ships() # to update after decrement
            self.aliens.empty() # clear aliens
            self.bullets.empty() # clear bullets
            self._create_fleet() # make a new fleet
            self.ship.center_ship()
            sleep(1) # sleep for 1 sec
        else:
            self.stats.game_active = False
            pygame.mouse.set_visible(True)  # for cursor to appear again
    
    def _check_aliens_bottom(self):
        """ if any alien reaches the bottom, the player loses a life """
        screen_rect = self.screen.get_rect()
        for alien in self.aliens.sprites():
            if alien.rect.bottom >= screen_rect.bottom:
                self._ship_hit()

    
    

if __name__ == '__main__':
    # Make a game instance, and run the game.
    ai = AlienInvasion()
    ai.run_game()


