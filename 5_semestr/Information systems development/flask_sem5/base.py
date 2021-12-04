class Middleware:
    def __call__(self, enviror, start_response):
        raise NotImplementedError


# m = Middleware(...) --> __init__
# m --> __call__
