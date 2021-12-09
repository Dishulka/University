import json
import requests

def get_token(username, password):
    headers = {'Content_Type0': 'application/json'}
    data = json.dumps({'username': username, 'password': password})
    response = requests.post('http://127.0.0.1:5001/token', data=data, headers=headers)
    return response.text


def make_get_requests(url, token):
    headers = {'Authorization': token}
    response = requests.get(url, headers=headers)
    return response.text


if __name__ == '__main__':
    token = get_token(username='admin', password='admin')
    print('token', token)
    result = make_get_requests('http://127.0.0.1:5001/get-money', token=token)
