from flask import Flask, render_template, request, redirect
from pymysql import connect

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')


@app.route('/greeting/<name>')
def greeting_handle(name):
    return f'Hello {name}'


@app.route('/users/<int:user_id>')
def search_user(user_id: int):
    users = [
        {'_id': 1, 'name': 'di1'},
        {'_id': 2, 'name': 'di2'},
        {'_id': 3, 'name': 'di3'}
    ]
    user = None
    for _user in users:
        if _user['_id'] == user_id:
            user = _user
            break
    if user is None:
        return 'Not found'
    return user


@app.route('/links')
def handle_links():
    action = request.args.get('action', None)
    #if 'action' in request.args:   Ravnosilno verhnemy
        #action = request.args['action']
    #else:
        #action = None

    if action == 'search':
        return redirect('/users/1')
    elif action == 'home':
        return redirect('/')
    return render_template('links.html')


@app.route('/form', methods=['GET', 'POST'])
def handle_form():
    if request.method == 'GET':
        return render_template('forms.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')

        if login and password:
            if login == 'kek' and password == 'lol':
                return 'OK'
        return 'Invalid login or password'


@app.route('/db/user', methods=['GET', 'POST'])
def search_user_db():
    if request.method == 'GET':
        return render_template('forms.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')

        connection = connect(host='127.0.0.1', user='root', password="dish0311", port=3306, db='labs')
        cursor = connection.cursor()
        _sql = f"select cl_id, Name from Client where login='{login}' and password='{password}'"
        cursor.execute(_sql)
        row_sql = cursor.fetchall() #возвращ список, где поле с юзер и т.д.
        connection.close()

        result = []
        for row in row_sql:
            result.append(dict(zip(['cl_id', 'Name'], row)))

        if not result:
            return 'Not found'
        return result[0]



if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)