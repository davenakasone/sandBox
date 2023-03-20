""" 
    Amortization of a loan refers to the process of paying off a loan with regular payments 
    over a specified period of time. 
    Each payment made towards the loan includes both principal and interest, 
    with the goal of gradually reducing the outstanding balance of the loan 
    until it is fully paid off.

    The payment amount is calculated using an amortization schedule, 
    which shows the breakdown of each payment into its principal and interest components, 
    as well as the remaining balance on the loan after each payment is made.

    In the early stages of a loan, a greater proportion of each payment goes towards paying off the interest, 
    while a smaller proportion goes towards the principal. 
    As the loan is gradually paid off, the proportion of each payment that goes towards the principal increases, 
    and the proportion that goes towards the interest decreases.

    By the end of the loan term, assuming all payments are made on time, 
    the outstanding balance on the loan will have been fully paid off, 
    and the loan will be considered fully amortized.
"""


def amortize_point_given_p_r_n_pd(P, r, n, period):
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
    PMT = P * r / (1 - (1+r)**(-n))
    
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


########~~~~~~~~END>  amortize_point_given_p_r_n_pd.py
