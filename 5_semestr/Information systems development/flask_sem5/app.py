from flask import Flask, request

from middleware.auth import AuthorizationMiddleware

app = Flask(__name__)
app.wsgi_app = AuthorizationMiddleware(app.wsgi_app)

users = {
    "1": {'name': 'admin', 'money': 100500},
    '2': {'name': 'ivan', 'money': 100},
    '3': {'name': 'sergey', 'money': 500}
}


@app.route('/get-money')
def get_money_headler():
    user_id = request.headers.get('auth_midelware_user')
    return json.dumps({'user_id': user_id, 'money': users.get(user_id, 0)})


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)