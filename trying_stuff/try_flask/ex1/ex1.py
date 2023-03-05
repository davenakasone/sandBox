"""
    $ flask --app ex1 --debug run
"""
from flask import Flask

# instance of Flask class is the WSGI application
# __name__ is where Flask looks for resources
app = Flask(__name__) 

# decorator tells Flask what URL should trigger the function
# do not name anything "flask.py"
@app.route('/')
def hiworld() :
    return "<h1>hi world</h1>"

if __name__ == '__main__' :
    app.run()