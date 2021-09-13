import os
from datetime import datetime
from flask import Flask, render_template

app = Flask(__name__)


@app.route('/') #  http://127.0.0.1:5001/
def index():
    return 'Hello from Flask'


@app.route('/greeting') #  http://127.0.0.1:5001/greeting
def greeting_handler():
    return 'Hello i am Flask'


@app.route('/info') #  http://127.0.0.1:5001/info
def info_handler():
    return f'Now: {datetime.now()}, PID: {os.getpid()}'


@app.route('/home') #  http://127.0.0.1:5001/home
def home_page_handler():
    return render_template('index.html')


@app.route('/home-dynamic') #  http://127.0.0.1:5001/home-dynamic
def home_page_dynamic_handler():
    context = {
        'name': 'Diana',
        'list_items': ['a', 'b', 'c'],
        'today': datetime.now()
    }
    return render_template('dynamic.html', **context) #return render_template('dynamic.html', name='Diana', list_items=items)


@app.route('/child') #  http://127.0.0.1:5001/child
def home_page_child_handler():
    return render_template('child.html')


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5001)
