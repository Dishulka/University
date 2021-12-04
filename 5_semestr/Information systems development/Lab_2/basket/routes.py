import json
from flask import Blueprint, render_template, request
from flask_table import Table, Col

from sql.SQLmaster import SQLmaster
from access import group_permission_decorator

basket_app = Blueprint('basket', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/configDataBase.json', 'r')))


@basket_app.route('/', methods=['GET', 'POST'])
@group_permission_decorator
def basket_index():
    result = SQLserver.request('list_orders.sql')

    '''table = ItemTable1(result)

    HTMLtable = table.__html__()
    file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
    file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')
    if HTMLtable == "<p>No Items</p>":
        file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
    else:
        file.write(HTMLtable)

    file.write('</div>{% endblock %}')
    file.close()

    return render_template('request_result_child.html', url_back='./betweenDate',
                           title=f'Заказы, сделаные в период с {date_min} по {date_max}')'''