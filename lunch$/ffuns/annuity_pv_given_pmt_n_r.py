""" 
    The present value of an annuity is the current value 
    of a series of equal periodic payments, discounted to their present value. 
    It represents the amount of money that would need to be invested now 
    to generate a stream of future cash flows.

    To calculate the present value of an annuity, you need to know the following variables:

        - The periodic payment amount
        - The number of payments
        - The discount rate or the rate of return required on the investment.

    the formula to calculate the present value of an annuity is:

        PV = C * [(1 - (1 + r)^-n) / r]

    PV = Present Value of the annuity
    C = Payment amount
    r = Discount rate or rate of return
    n = Number of payments
"""

from ._ffun_config import BAD_ARGUMENT_FLOAT
from ._ffun_config import WARN_RATE_LEVEL
from ._ffun_config import STR_WARN_RATE_LEVEL
from ._ffun_config import STR_NEGATIVE_ARGUMENT


def annuity_pv_given_pmt_n_r\
(
    payment           : float,
    number_of_periods : float,
    rate_per_period   : float
) -> float :
    """
    calculate present value of an annuity
        
    args :
        payment : value of the cashflow in a single period
        number_of_periods : how many time units receive the cashflow/payment
        rate_per_period : how much cashflows/payments accrue each period, percentage / 100
    
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
    a = (1 + rate_per_period) ** number_of_periods
    b = 1 / a
    c = 1 - b
    d = c / rate_per_period
    present_value = payment * d
    
    return present_value


########~~~~~~~~END>  annuity_pv_given_pmt_n_r.py
