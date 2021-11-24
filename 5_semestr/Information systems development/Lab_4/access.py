from functools import wraps
from flask import session, current_app, request, render_template


def group_permission_validation():
    return True

    '''
    access_config = current_app.config['ACCESS_CONFIG']
    group_name = session.get('group_name', 'Гость')
    target_app = request.endpoint.split(sep='.')
    
    if len(target_app) == 1:
        target_app = ""
    else:
        target_app = target_app[0]

    if group_name in access_config and target_app in access_config[group_name]:
        return True
    else:
        return False
    '''


def group_permission_decorator(f):
    @wraps(f)
    def wrapper(*args, **kwargs):
        if group_permission_validation():
            return f(*args, **kwargs)
        return render_template('permission_denied.html')

    return wrapper
