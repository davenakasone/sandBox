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

from .annuity_pv_given_pmt_n_r import annuity_pv_given_pmt_n_r


def annuity_pmt_given_n_r_pv\
(
    number_of_periods : float,
    rate_per_period   : float,
    present_value     : float
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
    P_sym, n_sym, PV_sym, r_sym = sympy.symbols('P, n, PV, r')
    
    # future value of the annuity equation
    PV_eq = sympy.Eq(PV_sym, P_sym * (1 - (1 + r_sym)**(-n_sym)) / r_sym)
    
    # get solutions
    p_sol = sympy.solve(PV_eq.subs([(PV_sym, present_value), (n_sym, number_of_periods), (r_sym, rate_per_period)]), P_sym)
    if p_sol is None :
        print("solver failed to find solution")
        return FAILED_CALCULATION_FLOAT
    
    # screen the solutions
    pmt_list = []
    for p_elm in p_sol :
        temp = p_elm.evalf()
        if temp.is_real :
            if (temp > 0) :
                pmt_list.append(p_elm)
    if len(pmt_list) == 0 :
        print(f"no valid solutions found")
        return FAILED_CALCULATION_FLOAT
    
    # test the solutions, just need 1 that works
    for pmt in pmt_list :
        pv = annuity_pv_given_pmt_n_r(pmt, number_of_periods, rate_per_period)
        if abs(pv - present_value) < ALLOWABLE_DIFFERENCE :
            return pmt
    return FAILED_CALCULATION_FLOAT


########~~~~~~~~END>  annuity_pmt_given_n_r_pv.py
