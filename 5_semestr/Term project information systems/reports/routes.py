from flask import Blueprint, render_template

reports_app = Blueprint('reports', __name__, template_folder='templates')


@reports_app.route('/')
def reports_index():
    return render_template('reports_index.html')
