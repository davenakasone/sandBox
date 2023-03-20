from ._ffun_config import WARN_RATE_LEVEL

def _valid_irate(irate:float) -> bool :
    if irate > WARN_RATE_LEVEL :
        return False
    else :
        return True

def _valid_nperiods(nperiods:float) -> bool :



...probably build this in to function parameters so they stand alone