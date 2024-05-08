import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        nome = request.form.get("n")
        mes = request.form.get("m")
        dia = request.form.get("d")

        id = db.execute("SELECT COUNT(id) FROM birthdays")
        print(id)
        db.execute("BEGIN")
        db.execute("INSERT INTO birthdays(id,name,month,day) VALUES(?,?,?,?)",(id[0]["COUNT(id)"]+1),nome,mes,dia)
        db.execute("COMMIT")
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        qry = db.execute("SELECT name,day,month FROM birthdays")
        return render_template("index.html",birth=qry)


