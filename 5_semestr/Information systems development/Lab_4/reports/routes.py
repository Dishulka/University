from flask import Blueprint, render_template
from access import group_permission_decorator

reports_app = Blueprint('reports', __name__, template_folder='templates')


@reports_app.route('/')
@group_permission_decorator
def reports_index():
    return render_template('reports_index.html')
