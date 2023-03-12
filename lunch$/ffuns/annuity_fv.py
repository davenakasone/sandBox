""" 
    The future value of an annuity is the value of a series of equal payments 
    at a future point in time, assuming compound interest. 
    In other words, it is the total amount of money that will accumulate in 
    an annuity over a period of time, taking into account the interest earned on the payments.

    FV = C * ((1 + r)^n - 1) / r

    FV is the future value of the annuity
    C is the payment amount
    r is the interest rate per period
    n is the number of periods
"""

from ._ffun_config import BAD_ARGUMENT_FLOAT
from ._ffun_config import WARN_RATE_LEVEL
from ._ffun_config import STR_WARN_RATE_LEVEL
from ._ffun_config import STR_NEGATIVE_ARGUMENT


def annuity_fv\
(
    payment           : float,
    number_of_periods : float,
    rate_per_period   : float
) -> float :
    """
    calculate future value of an annuity
        
    args :
        payment : value of the cashflow in a single period
        number_of_periods : how many time units receive the cashflow/payment
        rate_per_period : how much cashflows/payments accrue each period, percentage / 100
    
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
    a = (1 + rate_per_period) ** number_of_periods
    b = a - 1
    c = b / rate_per_period
    future_value = payment * c
    
    return future_value


########~~~~~~~~END>  annuity_fv.py
