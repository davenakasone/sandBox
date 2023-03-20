""" 
    period length must be consistent with the compounding frequency
    
    number of periods required for the present value to grow 
    to the future value, given a fixed interest rate.
    
    n = ln(FV/PV) / ln(1 + r)

    n  = the number of periods
    ln = the natural logarithm function
"""

import math

from ._ffun_config import BAD_ARGUMENT_FLOAT
from ._ffun_config import WARN_RATE_LEVEL
from ._ffun_config import STR_WARN_RATE_LEVEL
from ._ffun_config import STR_NEGATIVE_ARGUMENT


def lumpsum_n_given_r_pv_fv\
(
    rate_per_period : float,
    present_value   : float,
    future_value    : float
) -> float :
    """
    calculate periods needed to realize lump sum
        
    args :
        rate_per_period   : float, interest rate per period, percentage / 100
        present_value     : float, current value of the lump sum
        future_value      : float, current value of the lump sum
    
    return :
        future value as a float
    """
    
    # guards
    if rate_per_period < 0 :
        print(f"{STR_NEGATIVE_ARGUMENT}rate_per_period = {rate_per_period:0.3f}")
        return BAD_ARGUMENT_FLOAT
    if rate_per_period > WARN_RATE_LEVEL :
        print(f"{STR_WARN_RATE_LEVEL}rate_per_period = {rate_per_period:0.3f}")
    
    # calculation
    numerator = math.log(future_value / present_value)
    denominator = math.log(1 + rate_per_period)
    number_of_periods = numerator / denominator
    
    return number_of_periods


########~~~~~~~~END>  lumpsum_n_given_r_pv_fv.py
