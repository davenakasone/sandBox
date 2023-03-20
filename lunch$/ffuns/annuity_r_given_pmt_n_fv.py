""" 
    finding the rate, given future value of annuity, payment, and number of periods
    involves using iteration or a solver
    
    for ordinary annuities only
"""

import sympy

from ._ffun_config import BAD_ARGUMENT_FLOAT
from ._ffun_config import ALLOWABLE_DIFFERENCE
from ._ffun_config import FAILED_CALCULATION_FLOAT
from ._ffun_config import STR_NEGATIVE_ARGUMENT
from ._ffun_config import WARN_RATE_LEVEL

from .annuity_fv_given_pmt_n_r import annuity_fv_given_pmt_n_r


def annuity_r_given_pmt_n_fv\
(
    payment           : float,
    number_of_periods : float,
    future_value      : float
) -> float :
    """
    calculate future value of an annuity
        
    args :
        payment           : value of the cashflow in a single period
        number_of_periods : how many time units receive the cashflow/payment
        future_value      : how much cashflows/payments accrue each period, percentage / 100
    
    return :
        rate per period as float, if there is a solution
    """
    
    # guards
    if number_of_periods < 0 :
        print(f"{STR_NEGATIVE_ARGUMENT}number_of_periods = {number_of_periods}")
        return BAD_ARGUMENT_FLOAT
    
    # define the variables
    r_sym, P_sym, n_sym, FV_sym = sympy.symbols('r, P, n, FV')

    # future value of the annuity equation
    FV_eq = sympy.Eq(FV_sym, P_sym * ((1 + r_sym)**n_sym - 1) / r_sym)
    
    # get solutions
    r_sol = sympy.solve(FV_eq.subs([(FV_sym, future_value), (n_sym, number_of_periods), (P_sym, payment)]), r_sym)
    if r_sol is None :
        print("solver failed to find solution")
        return FAILED_CALCULATION_FLOAT
    
    # screen the solutions
    rate_list = []
    for r_i in r_sol :
        temp = r_i.evalf()
        if temp.is_real :
            if (temp > 0) and (temp < WARN_RATE_LEVEL) :
                rate_list.append(r_i)
    if len(rate_list) == 0 :
        print(f"no valid solutions found, rate 0% : {WARN_RATE_LEVEL:,.3%}")
        return FAILED_CALCULATION_FLOAT
    
    # test the solutions, just need 1 that works
    for rate in rate_list :
        fv = annuity_fv_given_pmt_n_r(payment, number_of_periods, rate)
        if abs(fv - future_value) < ALLOWABLE_DIFFERENCE :
            return rate
    return FAILED_CALCULATION_FLOAT


########~~~~~~~~END>  annuity_r_given_pmt_n_fv.py
