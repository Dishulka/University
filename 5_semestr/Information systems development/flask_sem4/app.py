import json

from flask import Flask, render_template, session

from user_scenario.routes import user_app
from scenario_auth.routes import auth_app

from access import group_validations_decorator, group_permission_validations

app = Flask(__name__)

app.register_blueprint(user_app, url_prefix='/user')
app.register_blueprint(auth_app, url_prefix='/auth')

dbconfig = json.load(open('config/configDataBase.json', 'r'))
app.config['DB_CONFIG'] = dbconfig
app.config['ACCESS_CONFIG'] = dbconfig


app.config['SECRET_KEY'] = 'my super secret key'


@app.route('/counter')
def counter():
    count = session.get('counter', None)
    if count is None:
        session['counter'] = 1
    else:
        session['counter'] = session['counter'] + 1 # Нельзя +=, там что-то перезаписывается
    return f'Your counter {session["counter"]}'


@app.route('/clear-session')
def clear_session():
    session.clear()
    # session.pop('counter') Удаляет только конкретное значение, а не всё
    return 'Cleaned'


'''
@app.route('/get-name')
@group_validations_decorator
def select_user():
    sql = provider.get('request1.sql')
    result = work_with_db(app.config)
    return str(result)'''


@app.route('/')
def index():
    return render_template('index.html')


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
