import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    """ find all holdings for each symbol & add up total # of shares"""
    rows = db.execute("""
        SELECT symbol, SUM(shares) as totalShares
        FROM transactions
        WHERE user_id = :user_id
        GROUP BY symbol
        HAVING totalShares > 0;
    """, user_id=session["user_id"])

    holdings = []
    totalCash = 0
    for row in rows:
        stock = lookup(row["symbol"])
        holdings.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": row["totalShares"],
            "price": usd(stock["price"]),
            "total": usd(stock["price"] * row["totalShares"])
        })
        totalCash += stock["price"] * row["totalShares"]

    """Get current user's cask baclance from 'users'"""
    rows = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])
    cash = rows[0]["cash"]
    totalCash += cash


    """send them to the summary table"""
    return render_template("index.html", holdings=holdings, cash=usd(cash), totalCash=usd(totalCash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()

        shares = request.form.get("shares")

        if not shares.isdigit():
            return apology("You cannot purchase partial shares.", 400)

        if not symbol:
            return apology("You must enter a symbol", 400)

        stock = lookup(symbol)
        if stock == None:
            return apology("Invalid symbol", 400)
        if not shares:
            return apology("You must enter a # of shares", 400)

        """"get cash amount for current user"""
        rows = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        cash = rows[0]["cash"]

        """calculate if they have enough in account to purchase"""
        newCash = cash - float(shares) * stock['price']
        if newCash < 0:
            return apology("Not enough money for purchase", 400)

        """update user's cash balance"""
        db.execute("UPDATE users SET cash=:newCash WHERE id=:id", newCash=newCash, id=session["user_id"])

        """record purchase into transaction table"""
        db.execute("""
            INSERT INTO transactions
                (user_id, symbol, shares, price)
            VALUES (:user_id, :symbol, :shares, :price)
            """,
            user_id=session["user_id"],
            symbol=stock["symbol"],
            shares=shares, price=stock["price"]
        )

        """display 'Purchase Successful! (function from importing flask)"""
        flash("Purchase Successful!")

        return redirect ("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("""
        SELECT symbol, shares, price, transacted
        FROM transactions
        WHERE user_id=:user_id
    """, user_id=session["user_id"])

    """change price to usd"""
    for i in range(len(transactions)):
        transactions[i]["price"] = usd(transactions[i]["price"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()

        if not symbol:
            return apology("No symbol entered", 400)
        stock = lookup(symbol)
        if stock == None:
            return apology("Invalid stock symbol", 400)
        return render_template("quoted.html", stockInfo={
            'name': stock['name'],
            'symbol': stock['symbol'],
            'price': usd(stock['price'])
        })
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure confirm password was submitted
        elif not confirmation:
            return apology("must provide password confirmation", 400)

        if password != confirmation:
            return apology("Passwords do not match", 400)

        try:
            result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=generate_password_hash(password))
        except:
            return apology("User already exists", 400)

        if result == None:
            return apology("Registration error", 400)

        # Remember which user has logged in
        session["user_id"] = result

        # Redirect user to home page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        stock = lookup(symbol)
        if not symbol:
            return apology("You must enter a symbol", 400)
        if not shares:
            return apology("You must enter a # of shares", 400)

        """Check if they have enough shares to sell"""
        rows = db.execute("""
            SELECT symbol, SUM(shares) as totalShares
            FROM transactions
            WHERE user_id=:user_id
            GROUP BY symbol
            HAVING totalShares > 0
        """, user_id=session["user_id"])

        for row in rows:
            if row["symbol"] == symbol:
                if shares > row["totalShares"]:
                    return apology("Not enough shares available", 400)

        """"get cash amount for current user"""
        rows = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        cash = rows[0]["cash"]

        """calculate new balance after selling"""
        newCash = cash + shares * stock['price']

        """update user's cash balance"""
        db.execute("UPDATE users SET cash=:newCash WHERE id=:id", newCash=newCash, id=session["user_id"])

        """record purchase into transaction table"""
        db.execute("""
            INSERT INTO transactions
                (user_id, symbol, shares, price)
            VALUES (:user_id, :symbol, :shares, :price)
            """,
            user_id=session["user_id"],
            symbol=stock["symbol"],
            shares= -1 * shares,
            price=stock["price"]
        )

        """display 'Purchase Successful! (function from importing flask)"""
        flash("Sale Successful!")
        return redirect ("/")
    else:
        """find all the symbols that the current user is holding & give as options in symbol field"""
        rows = db.execute("""
            SELECT symbol
            FROM transactions
            WHERE user_id=:user_id
            GROUP BY symbol
            HAVING SUM(shares) > 0;
        """, user_id=session["user_id"])
        return render_template("sell.html", symbols=[row["symbol"] for row in rows])

@app.route("/addCash", methods=["GET", "POST"])
@login_required
def addCash():
    """Add additional cash to balance."""
    if request.method == "POST":
        add = int(request.form.get("add"))
        if not add:
            return apology("No amount entered", 403)

        """Adjust new balance"""

        """"get cash amount for current user"""
        rows = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        cash = rows[0]["cash"]

        """calculate new balance after selling"""
        newCash = cash + add

        """update user's cash balance"""
        db.execute("UPDATE users SET cash=:newCash WHERE id=:id", newCash=newCash, id=session["user_id"])
        return redirect("/")
    else:
        return render_template("addCash.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
