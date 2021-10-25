from flask import Blueprint, render_template

user_app = Blueprint('user', __name__, template_folder='templates')


@user_app.route('/')
def greeting_user():
    return render_template('user-index.html')


@user_app.route('/get/<number>')
def get_user():
    return 'Get_User'


@user_app.route('/create')
def create_user():
    return 'create_user'


@user_app.route('/update')
def update_user():
    return 'update_user'
