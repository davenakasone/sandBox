"""
file routing, defined directories, and other control
"""
import os
from typing import List

# root of the data directory
DIR_DATA_BASE:str='/Users/davidnakasone/Desktop/semirealtimedata/_data/'

# where to find the tag file, this file has path of current working directory
ANCHOR_FILE:str=os.path.join(
    DIR_DATA_BASE,
    '__tag.txt'
)

# fields
TSTAMP:str='tstamp'
FIELDS_ALL:List[str]=[
    TSTAMP,
    'amps1',
    'amps2',
    'celsius1',
    'celsius2',
    'celsius3'
]
FIELDS_AMPS:List[str]=[
    amps for amps in FIELDS_ALL if 'amps' in amps
]
FIELDS_CELSIUS:List[str]=[
    celsius for celsius in FIELDS_ALL if 'celsius' in celsius
]


########~~~~~~~~END>  configurations.py
