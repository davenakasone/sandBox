"""
this is not real data, but will behave like a stream of real data
just adjust it to get your data
"""
import datetime
import pandas as pd
import sys
import os
from typing import Dict
import time
import random

sys.path.append(os.path.abspath('.'))
from configurations import (
    DIR_DATA_BASE,
    ANCHOR_FILE,
    TSTAMP,
    FIELDS_ALL,
    FIELDS_AMPS,
    FIELDS_CELSIUS
)


def runner(
    outfile_notes:str,
    sample_rate:float=1.0,
    outfile_dir_base:str=DIR_DATA_BASE,
    anchor_file:str=ANCHOR_FILE,
    debug:bool=True
)->None:
    """
    - only call once from the command line
    - sets up your data collection, polls, and updates datastream
    - the data stream is saved on every poll by appending to a csv
    - let it run...if it stops, your data colletion will have to be restarted
    """

    # establish the datetime stamp
    _dtnow = datetime.datetime.now()
    dtnow = _dtnow.astimezone()
    dts = dtnow.strftime('%y%m%d_%H%M%S%Z')
    if debug is True:
        print(dts)

    # establish a collector
    collector:Dict={
        field:[] for field in FIELDS_ALL
    }
    if debug is True:
        for k,v in collector.items():
            print(f'{k:<16s} : {len(v)} elements')

    # name a file to store the data
    ofile:str=os.path.join(
        outfile_dir_base,
        f'{dts}_{outfile_notes}.csv'
    )
    if debug is True:
        print(f'data will go here:\n\t{ofile}')

    # set the anchor file so data can be found later
    with open(anchor_file,'w') as fp:
        fp.write(f'{ofile}\n')
    if debug is True:
        print(f'reference the current data file with this anchor:\n\t{anchor_file}')

    # main loop
    rowcounter:int=0
    while True:
        # house keeping
        rowcounter+=1

        # collect the data
        for key in collector.keys():
            if key in FIELDS_AMPS:
                collector[key].append(random.uniform(0.0, 3.0))
            elif key in FIELDS_CELSIUS:
                collector[key].append(random.uniform(21.0, 55.0))
            elif key == TSTAMP:
                collector[TSTAMP].append(time.time())
            else:
                collector[key].append(-1.1)

        # write the data
        df=pd.DataFrame(
            {k:[v[-1]] for k,v in collector.items()}
        )
        if rowcounter==1:
            df.to_csv(ofile, index=False)
        else:
            df.to_csv(ofile, mode='a', index=False, header=False)

        # print info
        print(f'\nrow#{rowcounter}')
        if debug is True:
            for k,v in collector.items():
                if k!=TSTAMP:
                    print(f'{k:<16s} : {v[-1]:0.3f}')

        # wait to match the sample rate
        time.sleep(sample_rate)

# stand-alone
if __name__=='__main__':
    if len(sys.argv) == 2:
        runner(
            outfile_notes=sys.argv[1]
        )
    else:
        runner(
            outfile_notes='potatoe'
        )

    try:
        sys.exit(0)
    except:
        print(f'\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n')


########~~~~~~~~END>  runner.py
