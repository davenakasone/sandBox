""" 
    period length must be consistent with the compounding frequency
    
    The present value of a lump sum is the current value of a single future cash payment, 
    discounted to its current value using a specific interest rate. 
    In other words, it represents the amount of money that would need to be invested now 
    to generate a single future payment of the same amount at a specific interest rate.

    The formula for calculating the present value of a lump sum is:

        PV = FV / (1 + r)^n
    
    PV = present value of the lump sum
    FV = the future value of the lump sum
    r = the interest rate per period (expressed as a decimal)
    n = the number of periods over which the lump sum will grow

    The present value of a lump sum can be used in financial analysis to 
    compare the value of different investment opportunities or 
    to evaluate the cost of borrowing money over time. 
    It is also commonly used in retirement planning to determine 
    the amount of savings required to meet future financial goals.
"""

from ._ffun_config import BAD_ARGUMENT_FLOAT
from ._ffun_config import WARN_RATE_LEVEL
from ._ffun_config import STR_WARN_RATE_LEVEL
from ._ffun_config import STR_NEGATIVE_ARGUMENT


def lumpsum_pv\
(
    rate_per_period   : float,
    number_of_periods : float,
    future_value      : float
) -> float :
    """
    calculate the present value of a lumpsum
        
    args :
        rate_per_period   : float, interest rate per period, percentage / 100
        number_of_periods : float, periods of time to determine present value
        future_value      : float, expected value of the lump sum at end of specified periods
    
    return :
        present value as a float
    """
    
    # guards
    if rate_per_period < 0 :
        print(f"{STR_NEGATIVE_ARGUMENT}rate_per_period = {rate_per_period:0.3f}")
        return BAD_ARGUMENT_FLOAT
    if rate_per_period > WARN_RATE_LEVEL :
        print(f"{STR_WARN_RATE_LEVEL}rate_per_period = {rate_per_period:0.3f}")
    if number_of_periods < 0 :
        print(f"{STR_NEGATIVE_ARGUMENT}number_of_periods = {number_of_periods}")
        return BAD_ARGUMENT_FLOAT

    # calculation
    present_value = future_value / (1 + rate_per_period) ** number_of_periods
    
    return present_value


########~~~~~~~~END>  lumpsum_pv.py
