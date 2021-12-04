import json

from flask import Blueprint, render_template, request, session
from access import group_permission_decorator

from sql.SqlMaster import SQLMaster

auth_app = Blueprint('auth', __name__, template_folder='templates')

SQLServer = SQLMaster(json.load(open('config/configDataBase.json', 'r')))

LevelToName = {'0': 'Разработчик',
               '1': 'Админ',
               '2': 'Сотрудник'}


@auth_app.route('/', methods=['GET', 'POST'])
@group_permission_decorator
def auth_index():
    if request.method == 'GET':
        return render_template('auth_index.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')

        result = SQLServer.request('auth_group.sql', Login=login, Password=password)

        if len(result) == 0:
            return render_template('auth_failed.html')
        else:
            session['group_name'] = LevelToName[f"{result[0]['AccessLevel']}"]
            return render_template('auth_successfully.html', name=session['group_name'])



@auth_app.route('/unauth')
@group_permission_decorator
def auth_unauth():
    session.clear()
    return render_template('auth_unauth.html', name='Гость')
