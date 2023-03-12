""" 
    period length must be consistent with the compounding frequency
    
    The future value of a lump sum is the value of a single cash payment 
    that will grow over time with a fixed interest rate. 
    In other words, it represents the amount of money that a lump sum investment 
    or loan will be worth in the future, 
    after it has accrued interest over a certain period of time.

    The formula for calculating the future value of a lump sum is:

    FV = PV * (1 + r)^n

    FV = future value of the lump sum
    PV = the present value of the lump sum
    r = the interest rate per period (expressed as a decimal)
    n = the number of periods over which the lump sum will grow

    The future value of a lump sum can be used in financial analysis to determine 
    the expected return on an investment or the total cost of a loan over time. 
    It can also be used to calculate how much a lump sum will be worth 
    at a future date, which can be useful for retirement planning 
    or other long-term financial goals.
"""

from ._ffun_config import BAD_ARGUMENT_FLOAT
from ._ffun_config import WARN_RATE_LEVEL
from ._ffun_config import STR_WARN_RATE_LEVEL
from ._ffun_config import STR_NEGATIVE_ARGUMENT


def lumpsum_fv\
(
    rate_per_period   : float,
    number_of_periods : float,
    present_value     : float
) -> float :
    """
    calculate the future value of a lump sum
        
    args :
        rate_per_period   : float, interest rate per period, percentage / 100
        number_of_periods : float, periods of time to determine future value
        present_value     : float, current value of the lump sum
    
    return :
        future value as a float
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
    future_value = present_value * (1 + rate_per_period) ** number_of_periods
    
    return future_value


########~~~~~~~~END>  lumpsum_fv.py
