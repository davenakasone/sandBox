"""
exposes user to all sub-packages in "monotheist" collection
"""
import os
import sys
sys.path.append(os.path.abspath('.'))

# core code base
from ._config_monotheist import mcore

# circuit calculations
from ._config_monotheist import ccalc


########~~~~~~~~END>  __init__.py
