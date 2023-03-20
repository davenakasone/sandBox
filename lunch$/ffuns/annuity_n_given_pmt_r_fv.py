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
from ._ffun_config import STR_WARN_RATE_LEVEL

from .annuity_fv_given_pmt_n_r import annuity_fv_given_pmt_n_r


def annuity_n_given_pmt_r_fv\
(
    payment           : float,
    rate_per_period   : float,
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
    if rate_per_period < 0 :
        print(f"{STR_NEGATIVE_ARGUMENT}rate_per_period = {rate_per_period:.3%}")
        return BAD_ARGUMENT_FLOAT
    if rate_per_period > WARN_RATE_LEVEL :
        print(f"{STR_WARN_RATE_LEVEL}rate_per_period = {rate_per_period:0.3f}")
        
    # define the variables
    r_sym, P_sym, n_sym, FV_sym = sympy.symbols('r, P, n, FV')

    # future value of the annuity equation
    FV_eq = sympy.Eq(FV_sym, P_sym * ((1 + r_sym)**n_sym - 1) / r_sym)
    
    # get solutions
    n_sol = sympy.solve(FV_eq.subs([(FV_sym, future_value), (r_sym, rate_per_period), (P_sym, payment)]), n_sym)
    if n_sol is None :
        print("solver failed to find solution")
        return FAILED_CALCULATION_FLOAT
    
    # screen the solutions
    n_list = []
    for n_elm in n_sol :
        temp = n_elm.evalf()
        if temp.is_real :
            if temp > 0 :
                n_list.append(n_elm)
    if len(n_list) == 0 :
        print("no valid solutions found")
        return FAILED_CALCULATION_FLOAT
    
    # test the solutions, just need 1 that works
    for n in n_list :
        fv = annuity_fv_given_pmt_n_r(payment, n, rate_per_period)
        if abs(fv - future_value) < ALLOWABLE_DIFFERENCE :
            return n
    return FAILED_CALCULATION_FLOAT


########~~~~~~~~END>  annuity_n_given_pmt_r_fv.py
