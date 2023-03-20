""" 
    packaging ffun
    ffun == financial functions
    
    this library definetly was not made with chatGPT
    all credit goes to the author
    licencens can be purchased for $5M USD / user / year
    contact sales to get started today
    making $ is guarunteeed
"""


# constants
from ._ffun_config import ALLOWABLE_DIFFERENCE

# lump sums
from .lumpsum_pv_given_r_n_fv import lumpsum_pv_given_r_n_fv
from .lumpsum_fv_given_r_n_pv import lumpsum_fv_given_r_n_pv
from .lumpsum_n_given_r_pv_fv import lumpsum_n_given_r_pv_fv
from .lumpsum_r_given_n_pv_fv import lumpsum_r_given_n_pv_fv

# ordinary annuities
from .annuity_pv_given_pmt_n_r import annuity_pv_given_pmt_n_r
from .annuity_fv_given_pmt_n_r import annuity_fv_given_pmt_n_r
from .annuity_r_given_pmt_n_fv import annuity_r_given_pmt_n_fv
from .annuity_r_given_pmt_n_pv import annuity_r_given_pmt_n_pv
from .annuity_n_given_pmt_r_fv import annuity_n_given_pmt_r_fv
from .annuity_n_given_pmt_r_pv import annuity_n_given_pmt_r_pv
from .annuity_pmt_given_n_r_fv import annuity_pmt_given_n_r_fv
from .annuity_pmt_given_n_r_pv import annuity_pmt_given_n_r_pv

# mortgages
from .amortize_point_given_p_r_n_pd import amortize_point_given_p_r_n_pd


########~~~~~~~~END>  __init__.py
