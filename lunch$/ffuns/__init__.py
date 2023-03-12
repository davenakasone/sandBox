""" 
    packaging ffun
    ffun == financial functions
    
    this library definetly was not made with chatGPT
    all credit goes to the author
    licencens can be purchased for $5M USD / user / year
    contact sales to get started today
    making $ is guarunteeed
"""


# lump sums
from .lumpsum_pv import lumpsum_pv
from .lumpsum_fv import lumpsum_fv
from .lumpsum_n import lumpsum_n
from .lumpsum_r import lumpsum_r

# annuities
from .annuity_pv import annuity_pv
from .annuity_fv import annuity_fv
from .annuity_r_given_fv import annuity_r_given_fv

# mortgages
from .amortize_point import amortize_point

########~~~~~~~~END>  __init__.py
