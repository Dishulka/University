import json
from flask import Blueprint, render_template, request
from flask_table import Table, Col

from sql.SQLmaster import SQLmaster
from access import group_permission_decorator

requests_app = Blueprint('requests', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/configDataBase.json', 'r')))


class ItemTable1(Table):
    idOrder = Col('Номер заказа')
    NameCustomer = Col('Имя заказщика')
    ContactInfo = Col('Контактная информация')
    DateOrder = Col('Дата заказа')
    TotalCost = Col('Общая Стоимость')


class ItemTable2(Table):
    idOrder = Col('Номер заказа')
    NameCustomer = Col('Имя заказщика')
    contactInfo = Col('Контактная информация')


@requests_app.route('/')
@group_permission_decorator
def requests_index():
    return render_template('request_index.html')


@requests_app.route('/betweenDate', methods=['GET', 'POST'])
@group_permission_decorator
def requests_betweenDate():
    if request.method == 'GET':
        return render_template('request_betweenDate.html')
    else:
        date_min = request.form.get('date_min')
        date_max = request.form.get('date_max')
        result = SQLserver.request('request1.sql', Date1=date_min, Date2=date_max)

        table = ItemTable1(result)

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
                               title=f'Заказы, сделаные в период с {date_min} по {date_max}')


@requests_app.route('/SearchService', methods=['GET', 'POST'])
@group_permission_decorator
def requests_SearchService():
    if request.method == 'GET':
        return render_template('request_SearchService.html')
    else:
        name_Service = request.form.get('name_Service')
        result = SQLserver.request('request2.sql', NameService=name_Service)

        table = ItemTable2(result)

        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')
        if HTMLtable == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
        return render_template('request_result_child.html', url_back='./SearchService',
                               title=f'Заказы, где есть услуга: {name_Service}')
