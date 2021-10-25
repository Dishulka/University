import json

from flask import Flask, render_template

from user_scenario.routes import user_app

app = Flask(__name__)

app.register_blueprint(user_app, url_prefix='/user')

dbconfig = json.load(open('configDataBase.json', 'r'))
app.config['DB_CONFIG'] = dbconfig


@app.route('/')
def index():
    return render_template('index.html')


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
