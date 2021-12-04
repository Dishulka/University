from .base import Middleware
from werkzeug.wrappers import Request, Response


class AuthorizationMiddleware(Middleware):

    def __init__(self, wsgi_app):
        self.wsgi_app = wsgi_app

    def _generate_token(self, request):
        body = request.json
        try:
            if not isinstance(body, dict):
                raise TypeError('Invalid body type')
            username = body.get('username', '')
            password = body.get('password', '')
            if username == 'admin' and password == 'admin':
                user_id = '1'
                return self._encode_token(username, password, user_id)
        except TypeError:
            return None

    @staticmethod
    def _encode_token(self, username, password, user_id):
        try:
            token = request.headers.get('Au')
        return jwt.encode(
            payload={
                'username': username,
                'password': password,
                'user_id': user_id
            },
            key='my super key',
            algorithm='H5256'
        )

    def __call__(self, environ, start_reponse):
        request = Request(environ)
        if request.path == '/token' and request.method == 'POST':
            token = self._generate_token(request)
            if token is None:
                return Response('No such user or invalid request', status=401)(environ, start_reponse)
            return Response(token, status=200)(environ, start_reponse)
        else:
            user_id = self._decode_token(request)
            if user_id:
                environ['HTTP_AUTH_MIDDLEWARE_USER'] = user_id
                return self.wsgi_app(environ, start_reponse)
            return Response('Unauthorized', status=403)(environ, start_reponse)


# wsgi - наше приложение
# wsgi ("налаживает") стандарт взаимодействия http с flask
# Что такое wsgi интерфейс? - Рк№3