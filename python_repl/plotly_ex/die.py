from random import randint

class Die:
    """ a single unit...this isn't an english demo, so fuck you """

    def __init__(self, num_sides = 6):     # you can put a doceahedron in here if you want
        self.num_sides = num_sides  

    def roll(self):
        return randint(1, self.num_sides)   