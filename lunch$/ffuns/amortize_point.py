
def amortize_point(P, r, n, period):
    """
    Generates an amortization table for a loan at any given period.
    
    Arguments:
    P -- principal amount
    r -- interest rate per period
    n -- number of periods
    period -- period for which to generate the table (1-based index)
    
    Returns:
    A tuple containing:
    - The interest paid in the specified period
    - The principal paid in the specified period
    - The remaining balance after the specified period
    """
    # Calculate periodic payment using the formula for the present value of an annuity
    PMT = P*r/(1 - (1+r)**(-n))
    
    # Initialize remaining balance and running totals
    balance = P
    total_interest = 0
    total_principal = 0
    
    # Calculate the interest and principal paid for each period
    for i in range(1, n+1):
        interest = balance*r
        total_interest += interest
        
        if i == period:
            return interest, PMT - interest, balance
        
        principal = PMT - interest
        total_principal += principal
        balance -= principal
    
    # Raise an error if the specified period is out of range
    raise ValueError("Period out of range.")

########~~~~~~~~END>  amortize_point.py
