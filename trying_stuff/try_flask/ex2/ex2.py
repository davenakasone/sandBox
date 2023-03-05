"""
    $ flask --app ex2 --debug run
    prevent injection attacks with markupsafe
"""

import markupsafe
from flask import Flask


# instance of Flask class is the WSGI application
# __name__ is where Flask looks for resources
app = Flask(__name__) 

# decorator tells Flask what URL should trigger the function
# do not name anything "flask.py"
@app.route('/<name>')
def hiworld(name:str="galaleroy") :
    return f"Hi, {markupsafe.escape(name)}"

if __name__ == '__main__' :
    app.run()