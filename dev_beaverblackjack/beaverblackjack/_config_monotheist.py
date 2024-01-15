"""
where sub-packages are imported
"""
import os
import sys
sys.path.append(os.path.abspath('.'))

# core code base
from . import monotheist_core as mcore

# circuit calculations
from . import circuit_calculations as ccalc


########~~~~~~~~END>  _config_monotheist.py
