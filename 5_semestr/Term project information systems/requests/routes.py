import json

from flask import Blueprint, render_template, request
from flask_table import Table, Col

from access import group_permission_decorator
from sql.SqlMaster import SQLMaster

requests_app = Blueprint('requests', __name__, template_folder='templates')

SQLServer = SQLMaster(json.load(open('config/configDataBase.json', 'r')))


class ItemTableRequestEmployee(Table):
    Name = Col('Имя сотрудника')
    Position = Col('Должность')


class ItemTableRequestCar(Table):
    idCar = Col('Номер машины')
    Brand = Col('Марка')
    CarYear = Col('Год выпуска')
    LicensePlateNumber = Col('Лицензионный номер')


class ItemTableRequestConsignmentNote(Table):
    MonthNoteDate = Col('Месяц оформления ТТН')
    countTTN = Col('Количество ТТН')


class ItemTableRequestTotalWeight(Table):
    Name = Col('Имя клиента')
    sumWeight = Col('Суммарный вес')


@requests_app.route('/')
@group_permission_decorator
def requests_index():
    return render_template('request_index.html')


@requests_app.route('/request_employee', methods=['GET', 'POST'])
@group_permission_decorator
def requests_employee():
    if request.method == 'GET':
        return render_template('request_employee.html')
    else:
        year = request.form.get('year')
        month = request.form.get('month')
        result = SQLServer.request('request_hired_employee.sql', year=year, month=month)

        table = ItemTableRequestEmployee(result)

        HTML_table = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTML_table == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTML_table)

        file.write('</div>{% endblock %}')
        file.close()

        return render_template('request_result_child.html', url_back='./request_employee',
                               title=f'Сотрудники, которые были наняты в месяце - {month}, в году - {year}')


@requests_app.route('/request_car', methods=['GET', 'POST'])
@group_permission_decorator
def requests_car():
    if request.method == 'GET':
        return render_template('request_car.html')
    else:
        car_year = request.form.get('car_year')
        result = SQLServer.request('request_car_year.sql', carYear=car_year)
        table = ItemTableRequestCar(result)

        HTML_table = table.__html__()

        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTML_table == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTML_table)
        file.write('</div>{% endblock %}')
        file.close()

        return render_template('request_result_child.html', url_back='./request_car',
                               title=f'Машины, у которой год выпуска: {car_year}')


@requests_app.route('/request_consignment_note', methods=['GET', 'POST'])
@group_permission_decorator
def requests_consignment_note():
    if request.method == 'GET':
        return render_template('request_consignment_note.html')
    else:
        year = request.form.get('year')
        result = SQLServer.request('request_consignment_note_year.sql', year=year)

        for temp in result:
            temp['MonthNoteDate'] = temp['MONTH(NoteDate)']
            del temp['MONTH(NoteDate)']
        for temp in result:
            temp['countTTN'] = temp['COUNT(idConsignmentNote)']
            del temp['COUNT(idConsignmentNote)']
        table = ItemTableRequestConsignmentNote(result)

        HTML_table = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTML_table == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTML_table)

        file.write('</div>{% endblock %}')
        file.close()

        return render_template('request_result_child.html', url_back='./request_consignment_note',
                               title=f'Количество ТТН, которые оформили в {year} году')


@requests_app.route('/request_total_weight', methods=['GET', 'POST'])
@group_permission_decorator
def requests_total_weight():
    if request.method == 'GET':
        return render_template('request_total_weight.html')
    else:
        year = request.form.get('year')
        result = SQLServer.request('request_total_weight_year.sql', year=year)

        for temp in result:
            temp['sumWeight'] = temp['SUM(Weight)']
            del temp['SUM(Weight)']
        table = ItemTableRequestTotalWeight(result)

        HTML_table = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTML_table == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTML_table)

        file.write('</div>{% endblock %}')
        file.close()
        return render_template('request_result_child.html', url_back='./request_total_weight',
                               title=f'Суммарный вес клиентов за {year} год')
