from flask import Flask, render_template, request, flash

app = Flask(__name__)
app.secret_key = "password"

@app.route("/start")
def index() :
    flash("input your name : ")
    return render_template("index.html") # good in template folder

@app.route("/greet", methods=['POST', 'GET'])
def greet():
    flash(f"{str(request.form['name_input'])} is bad.")
    return render_template("index.html")
    