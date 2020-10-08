import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd
from datetime import datetime

#API_KEY = "pk_79c10d67edb543c58f3aa55ebd2bcbfc"

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    cash = db.execute("SELECT cash FROM users WHERE id = :x", x=session["user_id"])[0]["cash"]
    #print(cash)
    owns = db.execute("SELECT symbol, shares, elder_price FROM owned WHERE user_id = :x",x=session["user_id"])
    #print(owns)
    infos = []
    i = 0
    total = 0
    for item in owns:
        infos.append([])
        infos[i].append(item["symbol"])
        infos[i].append(lookup(item["symbol"])["name"])
        infos[i].append(item["shares"])
        infos[i].append(lookup(item["symbol"])["price"])
        curr = item["shares"]*lookup(item["symbol"])["price"]
        total += curr
        infos[i].append(curr)
        infos[i].append(item["elder_price"])
        i += 1
    return render_template("index.html", infos=infos, cash = cash, total = total + cash)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You must provide symbol", 400)
        count = request.form.get("shares")
        #check count
        if not count:
            return apology("You must provide shares")
        count = int(count)
        if count < 0:
            return apology("Shares must be a positive number", 400)
        if count == 0:
            return apology("Zero ?", 400)
        cash = db.execute("SELECT cash FROM users WHERE id = :x", x=session["user_id"])[0]["cash"]
        row = lookup(symbol)
        if not row:
            return apology("Symbol is not found", 400)
        price = row["price"]
        if price*count > cash:
            return apology("Your cash is not enough to buy shares", 400)
        new_cash = cash - (price*count)
        db.execute('UPDATE users SET cash=:x WHERE rowid = :y', x=new_cash, y=session["user_id"])
        db.execute("INSERT INTO operations(user_id, date, price, shares, type, symbol) VALUES(:id, :date, :price, :share, 'buy', :sym)",
           id=session["user_id"], date=datetime.now(), price=price, share=count, sym=symbol)
        flag = db.execute("SELECT shares FROM owned WHERE user_id = :x and symbol = :y", x=session["user_id"], y = symbol)
        if not flag:
            db.execute("INSERT INTO owned(symbol, shares, user_id, elder_price) VALUES(:sym, :share, :id, :p)", sym=symbol, share = count, id = session["user_id"], p=price)
        else:
            db.execute('UPDATE owned SET shares=shares+:x WHERE user_id = :y and symbol=:sym', x=count, y=session["user_id"], sym=symbol)
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    infos = db.execute("SELECT * FROM operations WHERE user_id = :id", id=session["user_id"])
    #print(infos)
    return render_template("history.html", infos=infos)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You must provide a symbol", 400)
        else:
            row = lookup(symbol)
            if not row:
                return apology("Symbol is not found", 400)
            else:
                return render_template("quoted.html", row=row)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirm = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        elif not confirm:
            return apology("must provide confirm password", 400)

        rows = db.execute("SELECT username from users WHERE username = :x", x = username)
        print(rows)
        if rows:
            return apology("username is not avaliable")

        elif confirm != password:
            return apology("Passwords didn't match", 400)

        hash = generate_password_hash(password)
        db.execute("INSERT INTO users(username, hash) VALUES(:x, :y)",x = username, y = hash)
        user_id = db.execute("SELECT id FROM users WHERE hash = :x",x =hash)[0]
        session["user_id"] = user_id["id"]
        # Redirect user to home page

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You must provide symbol", 400)
        count = request.form.get("shares")
        #check count
        if not count:
            return apology("You must provide shares")
        count = int(count)
        if count < 0:
            return apology("Shares must be a positive number", 400)
        if count == 0:
            return apology("Zero ?", 400)
        cash = db.execute("SELECT cash FROM users WHERE id = :x", x=session["user_id"])[0]["cash"]
        row = lookup(symbol)
        if not row:
            return apology("Symbol is not found", 400)
        price = row["price"]
        new_cash = cash + (price*count)
        flag = db.execute("SELECT shares FROM owned WHERE user_id = :x and symbol = :y", x=session["user_id"], y = symbol)
        if not flag:
            text = "You don't have" + symbol + " shares"
            apology(text, 400)
        else:
            shares = flag[0]["shares"]
            if shares < count:
                text = "You have " + str(shares) + " " + symbol + " shares"
                return apology(text, 400)
            if shares == count:
                db.execute('DELETE from owned WHERE user_id = :y and symbol=:sym', y=session["user_id"], sym = symbol)
            else:
                db.execute('UPDATE owned SET shares=shares-:x WHERE user_id = :y and symbol=:sym', x=count, y=session["user_id"], sym = symbol)
            db.execute('UPDATE users SET cash=:x WHERE rowid = :y', x=new_cash, y=session["user_id"])
            db.execute("INSERT INTO operations(user_id, date, price, shares, type, symbol) VALUES(:id, :date, :price, :share, 'sell', :sym)",
                id=session["user_id"], date=datetime.now(), price=price, share=count, sym=symbol)
        return redirect("/")
    else:
        return render_template("sell.html")


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    if request.method == "POST":
        elder = request.form.get("elder_password")
        password = request.form.get("password")
        confirm = request.form.get("confirm")
        hash = db.execute("SELECT hash FROM users WHERE id = :id", id=session["user_id"])[0]["hash"]
        if not check_password_hash(hash, elder):
            return apology("Your password is wrong")
        elif password != confirm:
            return apology("New passwords didn't match")
        new_hash = generate_password_hash(password)
        db.execute("UPDATE users SET hash=:new WHERE id=:id",new = new_hash, id=session["user_id"])
        return redirect("/")
    else:
        return render_template("change.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
