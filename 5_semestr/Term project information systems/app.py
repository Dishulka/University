from flask import Flask, render_template
from reports.routes import reports_app
from requests.routes import requests_app

app = Flask(__name__)

app.config['TEMPLATES_AUTO_RELOAD'] = True

app.register_blueprint(requests_app, url_prefix='/requests')
app.register_blueprint(reports_app, url_prefix='/reports')


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/exit')
def exit():
    return render_template('exit.html')


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
