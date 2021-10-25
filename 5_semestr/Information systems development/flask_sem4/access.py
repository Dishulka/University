'''def decor(f):
    def wrapper(*args, **kwargs):
        print('Before')
        return f(*args, **kwargs)
    return wrapper


@decor
def sum(a, b):
    return a + b


print(sum(1, 2))'''

from flask import sessions, current_app, request


def group_validations(f):
    group_name = sessions.get('group_name', '')
    if group_name:
        return True
    return False


def group_validations_decorator(f):
    #wraps(f)
    def wrapper(*args, **kwargs):
        if group_validations():
            return f(*args, **kwargs)
        return 'Permission denided'
    return wrapper


def group_permission_validations():
    access_config = current_app.config['ACCESS_CONFIG']
    group_name = sessions.get('group_name', 'unauthorized')

    # request.endpoint = /auth/login => 'auth.login_page' = ['auth', 'login_page']
    # request.endpoint = /get-name => 'select_user' = ['select_user']


    target.app = "" if len(request.endpoint.slit('.')) == 1 else request.endpoint.split('.')[0]

    if group_name in acess_config and target_app in access_config[group, name]:
        return True
    return False


def group_permission_decorator(f):
    @wraps(f)
    def wrapper(*args, **kwargs):
        if group_permission_validations():
            return f(*args, **kwargs)
        return 'Permission denided'
    return wrapper


'''
def sum(a, b):
    return a + b


decor_func = group_validations_decorator(sum)
print(decor_func.__name__)'''