import json
from flask import Blueprint, render_template, request, session
from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

auth_app = Blueprint('auth', __name__, template_folder='templates')


LevelToName = {'0': 'Пользователь',
               '1': 'Админ'}


@auth_app.route('/', methods=['GET', 'POST'])
@group_permission_decorator
def auth_index():
    if request.method == 'GET':
        return render_template('auth_index.html')
    else:
        SQLserver = SQLmaster(json.load(open('config/configDataBase.json', 'r')))
        login = request.form.get('login')
        password = request.form.get('password')

        result = SQLserver.request('requestGroup.sql')

        for accessRights in result:
            if login == accessRights['Login'] and password == accessRights['Password']:
                session['group_name'] = LevelToName[f"{accessRights['AccessLevel']}"]
                return render_template('auth_successfully.html', name=session['group_name'])

        return render_template('auth_failed.html')


@auth_app.route('/unauth')
@group_permission_decorator
def auth_unauth():
    session.clear()
    return render_template('auth_unauth.html', name='Гость')
