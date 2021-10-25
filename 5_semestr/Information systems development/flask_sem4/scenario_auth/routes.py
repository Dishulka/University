from flask import Blueprint, sessions, render_template, request

auth_app = Blueprint('auth', __name__, template_folder='templates')


@auth_app.route('/login', methods=['GET', 'POST'])
def login_page():
    if request.method == 'GET':
        return render_template('login.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')

    if login == 'admin' and password == 'admin':
        sessions['group_name'] = 'admin'
        return 'logged in'
    if login == 'typical' and password == 'typical':
        sessions['group_name'] = 'typical'
        return 'logged in'
    return 'Invalid login or password'