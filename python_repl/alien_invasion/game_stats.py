class GameStats:
    """ holds game results, stats, ect """

    def __init__(self, ai_game):
        """ constructor """
        self.high_score = 0 # shouldn't be reset so initialized here
        self.settings = ai_game.settings
        self.reset_stats()
        self.game_active = False   # starts false so [play] button pushed, false when 3 lives used
    
    def reset_stats(self): # for player starting a new game...instead of deleting instance and making a new one
        """ initializes statistics the game follows """
        self.ships_left = self.settings.ship_limit
        self.score = 0 # reset score
        self.level = 1 # begin on level 1
