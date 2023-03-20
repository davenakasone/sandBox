""" 
    period length must be consistent with the compounding frequency
    
    To determine the effective interest rate per period (r) of 
    a lump sum investment or loan, given the present value (PV), 
    future value (FV), and the number of periods (n)

    r = (FV / PV)^(1/n) - 1
        ^ is the exponentiation operator

    This formula calculates the interest rate per period required for 
    the present value to grow to the future value over the given number of periods. 
    The effective interest rate takes into account the effect of compounding, 
    which is the process of earning interest on interest.
"""

from ._ffun_config import BAD_ARGUMENT_FLOAT
from ._ffun_config import STR_NEGATIVE_ARGUMENT


def lumpsum_r_given_n_pv_fv\
(
    number_of_periods : float,
    present_value     : float,
    future_value      : float
) -> float :
    """
    calculate periods needed to realize lump sum
        
    args :
        number_of_periods : float, periods seperating present and future values
        present_value     : float, current value of the lump sum
        future_value      : float, current value of the lump sum
    
    return :
        future value as a float
    """
    
    # guards
    if number_of_periods < 0 :
        print(f"{STR_NEGATIVE_ARGUMENT}number_of_periods = {number_of_periods}")
        return BAD_ARGUMENT_FLOAT
    
    # calculation
    rate_per_period = ((future_value / present_value) ** (1 / number_of_periods)) - 1
    
    return rate_per_period


########~~~~~~~~END>  lumpsum_r_given_n_pv_fv.py
