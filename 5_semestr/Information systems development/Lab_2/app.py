import json
from flask import Flask, render_template, sessions, session
from access import group_permission_decorator
from auth.routes import auth_app
from requests.routes import requests_app
from reports.routes import reports_app

app = Flask(__name__)

app.config['ACCESS_CONFIG'] = json.load(open('config/configAccess.json', 'r', encoding="utf-8"))
app.config['SECRET_KEY'] = 'Secret'
app.config['TEMPLATES_AUTO_RELOAD'] = True

app.register_blueprint(auth_app, url_prefix='/auth')
app.register_blueprint(requests_app, url_prefix='/requests')
app.register_blueprint(reports_app, url_prefix='/reports')


@app.route('/')
@group_permission_decorator
def index():
    return render_template('index.html', name=session.get('group_name', 'Гость'))


@app.route('/exit')
@group_permission_decorator
def exit():
    return render_template('exit.html')


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
