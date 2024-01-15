"""
generic custom exception class
used throughout the "monotheist" package

use-case #1, the try block
    try :
        x = 9
        y = 0
    except Exception as e :
        raise FlagEx(
            fun=__name__,
            msg=f'{x}/{y}, division by 0...',
            ethrown=e
        )

use-case #2, guarding
    if len(infile) < 1 or infile is None :
        raise FlagEx(
            fun=__name__,
            msg=f'no file to read',
            ethrown=None
        )
"""


class FlagEx(Exception) :
    """
    - general purpouse exception for "monotheist" package
    - do not use for situations requiring unique exception handling
    """

    def __init__(
        self,
        fun:str,
        msg:str,
        ethrown:Exception = None
    ) :
        """instance made when raising an exception"""
        print(f'!!! {fun}()')
        print(f'{msg}')
        if ethrown is not None :
            print(f'{type(ethrown)}, {ethrown}')


########~~~~~~~~END>  FlagEx.py
