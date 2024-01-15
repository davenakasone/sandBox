"""
for 2 paralell resistors
"""

from .._config_circuit_calculations import mcore

import math


def r2(
    r_a : float,
    r_b : float,
    debug : bool = False
) -> float :
    """
    given 2 resistors in parallel, find equivelent resistance

    @params
        r_a : float, value of first resistor, in ohms
        r_b : float, value of second resistor, in ohms
        debug : bool = False, make True to print during execution
    
    @returns
        float, equilvelent resistance in ohms
    
    @ notes
        - can chain together calls
        - designed for 2 resistors, no complex Z
    """

# guard NaNs
    if math.isnan(r_a) is True :
        raise mcore.FlagEx(
            fun=__name__,
            msg=f'r_a is NaN',
            ethrown=None
        )
    if math.isnan(r_b) is True :
        raise mcore.FlagEx(
            fun=__name__,
            msg=f'r_b is NaN',
            ethrown=None
        )

# guard negatives
    if r_a < 0.0 :
        raise mcore.FlagEx(
            fun=__name__,
            msg=f'r_a is negative: {r_a:e}',
            ethrown=None
        )
    if r_b < 0.0 :
        raise mcore.FlagEx(
            fun=__name__,
            msg=f'r_b is negative: {r_b:e}',
            ethrown=None
        )

# guard short
    if r_a==0.0 or r_b==0.0 :
        if debug is True :
            print('equivelent resistance is a short')
        return 0.0

# calculate the equivelent parallel resistance
    rpara : float = (r_a * r_b) / (r_a + r_b)

# check the result
    if math.isnan(rpara) is True :
        raise mcore.FlagEx(
            fun=__name__,
            msg=f'result is NaN',
            ethrown=None
        )
    if rpara < 0.0 :
        raise mcore.FlagEx(
            fun=__name__,
            msg=f'resistance is negative: {rpara:e}',
            ethrown=None
        )

# done
    if debug is True :
        print(f'{r_a:e} || {r_b:e} = {rpara:e} ohms')

    return rpara


########~~~~~~~~END>  r2.py
