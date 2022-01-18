"""
if you keep the setting here, you don't have to go looking for them
notice the head class (AlienInvasion) took this class in by compositon under the attribute 'settings'

for the ship to move 1 pixel at a time, get an attribute that lets you adjust it
floats allow for better adjustment, but rectangle coordinates only take integers

some shooting features will be added
"""

class Settings:
    """ this class will hold all the setting for the game """
    
    def __init__(self):
        """ initialize game's seetings """
        self.screen_width = 1_000
        self.screen_height = 700
        self.bg_color = (230, 230, 230)
        self.speedup_scale = 1.1             # increase speed every level / fleet kill
        self.score_scale = 1.5               # point value increases with difficulty
        self.initialize_dynamic_settings()

        # aliens
        self.fleet_drop_speed = 20            # keep as integer....rate UFOs attack at, increases if horz does
        
        # for ship
        self.ship_limit = 3

        # for shooting
        self.bullet_width = 5
        self.bullet_height = 20
        self.bullet_color = (0, 60, 60)
        self.bullets_allowed = 1_0
        self.bullet_pen = False                  # False for penetrate, True for no penetration
        self.bullet_burst = False                # if True, space bar makes a burst of 10 instead of just 1
        self.bullet_pulses = 10          # how many bullets shot with one key press (burst must be true)
        self.nuke_color = (255,0,0)
        self.nuke_width = self.screen_width - 10
        self.nuke_height = 20
        self.nuke_speed = 1.0
        self.nuke_limit = 10
    
    def initialize_dynamic_settings(self):
        """ continue to update constructor base attributes """
        self.ship_speed = 1.4                # adjust to control speed of ship
        self.alien_speed = 3.1               # adjust to control horizontal speed of aliens
        self.bullet_speed = 1.7
        self.fleet_direction = 1             # right is 1, -1 is left    they start moving right
        self.alien_points = 50   # points here so they can increase as level does
        self.nuke_limit = 10   # reset nukes
    
    def increase_speed(self):
        """ call to increase speed of these elements dynamic """
        self.ship_speed *= self.speedup_scale
        self.alien_speed *= self.speedup_scale
        self.bullet_speed *= self.speedup_scale
        self.alien_points = int(self.alien_points * self.score_scale)
        #print("aliens are now worth: ", self.alien_points) # for testing
