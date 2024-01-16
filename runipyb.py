"""
run ipynb if you don't want to press buttons
https://papermill.readthedocs.io/en/latest/usage-execute.html

find your venv
>>> import sys
>>> sys.executable
/Users/davidnakasone/Desktop/dkn/bin/python3.11

jupyterlab, use this
/opt/homebrew/Cellar/jupyterlab/4.0.10
or
brew info jupyterlab

$ jupyter lab
...
"""

import os
import sys
import papermill as pm


def runipynb(
    nb_input : str,
    nb_output : str,
    nb_params : dict = None,
    debug : bool = False
) -> str :
    """
    run an ipynb
    """
    
    if nb_params is None :
        pm.execute_notebook(
            input_path=nb_input,
            output_path=nb_output
        )
    else :
        pm.execute_notebook(
            input_path=nb_input,
            output_path=nb_output,
            parameters=nb_params
        )

# done
    return nb_output


# for direct CLI execution
if __name__ == '__main__' :

# no params to pass
    runipynb(
        nb_input=os.path.join(os.path.abspath('.'), 'template_no_param.ipynb'),
        nb_output=os.path.join(os.path.abspath('.'), 'ouput_no_param.ipynb'),
        nb_params=None,
        debug=True
    )

# with params to pass
    runipynb(
        nb_input=os.path.join(os.path.abspath('.'), 'template_with_param.ipynb'),
        nb_output=os.path.join(os.path.abspath('.'), 'ouput_with_param.ipynb'),
        nb_params=dict(a='c++ is bad', x=3),
        debug=True
    )


########~~~~~~~~END>  runipynb.py
