from flask import Flask, send_from_directory

app = Flask(__name__)

@app.route("/")
def index():
    return send_from_directory(".", "index.html")

@app.route("/breakout.<ext>")
def breakout(ext):
    return send_from_directory(".", "breakout.{}".format(ext))
