"""
    setting up an oscillator
    LTC 6692 (1, 2, 3, or 4)
    optimized for Ndiv == 4, because [15.63kHz < f < 250 kHz] for all cases
"""

class Ltc6992 :
    FAILURE = "selection does not match device specifications"
    f_init = -999.999

    def __init__(self, f: float, D: float, p: int, iname: str) :
        self.Rn_top = 976.0
        self.Rn_bot = 102.0
        self.Vdiv = 5 * (self.Rn_bot / (self.Rn_bot + self.Rn_top))
        self.ndiv = 4.0
        
        self.frequency = self.f_init
        self.duty = self.f_init
        self.polarity = self.f_init
        self.period = self.f_init
        
        self.Rs_top = self.f_init
        self.Rs_bot = self.f_init
        self.Rs = self.f_init
        self.Vmod = self.f_init
        
        self.name = iname
        self.start(f, D, p)
    
    
    def start(self, frq: float, dut: float, pol: int) :
        if (frq < 15.63e3) or (frq > 250.0e3) or (dut < 0.0) or (dut > 1.0) or ((pol != 0) and(pol != 1)) :
            print(f"{self.FAILURE}")
            return
        if pol == 0 :
            self.Rn_top = 976.0
            self.Rn_bot = 102.0
        else :
            self.Rn_top = 102.0
            self.Rn_bot = 976.0
        self.Vdiv = 5 * (self.Rn_bot / (self.Rn_bot + self.Rn_top))
        
        self.frequency = frq
        self.duty = dut
        self.polarity = pol
        self.period = 1 / self.frequency
        self.Rs = 50.0e9/(self.ndiv * self.frequency)
        self.Rs_bot = self.Rs * (self.duty + (1/8)) * 0.8
        self.Rs_top = self.Rs - self.Rs_bot
        self.Vmod = self.Rs_bot / (self.Rs_bot + self.Rs_top)
        self.duty = (self.Vmod / 0.8) - (1/8)
    
    
    def oprint(self) :
        print(f"\noscillator '{self.name}'")
        print(f"f         : {self.frequency/1.0e3:0.3f} kHz")
        print(f"T         : {self.period*1.0e6:0.3f} us")
        print(f"D         : {self.duty*100:0.3f} %")
        print(f"pol       : {self.polarity}")
        print(f"Ndiv      : {self.ndiv}")
        print(f"R_div top : {self.Rn_top}")
        print(f"R_div bot : {self.Rn_bot}")
        print(f"Vdiv      : {self.Vdiv:0.2f}V")
        print(f"Rset      : {self.Rs/1.0e3:0.1f}k")
        print(f"set top   : {self.Rs_top/1.0e3:0.1f}k")
        print(f"set bot   : {self.Rs_bot/1.0e3:0.1f}k")
        print(f"Vmod      : {self.Vmod:0.2f}V")
        

########~~~~~~~~END>  ltc6992.py
