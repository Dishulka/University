import json
from flask import Blueprint, render_template, request
from flask_table import Table, Col
from sql.SQLmaster import SQLmaster
from access import group_permission_decorator

requests_app = Blueprint('requests', __name__, template_folder='templates')

SQLserver = SQLmaster(json.load(open('config/configDataBase.json', 'r')))


class ItemTableRequest1(Table):
    Surname = Col('Имя сотрудника')
    Position = Col('Должность')


class ItemTableRequest2(Table):
    idEmployee = Col('Номер сотрудника')
    Surname = Col('Имя сотрудника')
    Section = Col('Отдел сотрудника')
    HiredDate = Col('Дата приема на работу')
    FiredDate = Col('Дата увольнения')
    Birthday = Col('День рождение')
    Position = Col('Должность')


class ItemTableRequest3(Table):
    idCar = Col('Номер машины')
    Brand = Col('Марка')
    CarYear = Col('Год выпуска')
    LicensePlateNumber = Col('Лицензионный номер')


class ItemTableRequest4(Table):
    MonthNoteDate = Col('Месяц оформления ТТН')
    countTTN = Col('Количество ТТН')


class ItemTableRequest5(Table):
    idClient = Col('Номер клиента')
    sumWeight = Col('Суммарный вес')


class ItemTableRequest6(Table):
    MonthNoteDate = Col('Месяц оформления ТТН')
    avgWeight = Col('Средний вес')


@requests_app.route('/')
@group_permission_decorator
def requests_index():
    return render_template('request_index.html')


@requests_app.route('/request1', methods=['GET', 'POST'])
@group_permission_decorator
def requests_request1():
    if request.method == 'GET':
        return render_template('request_1.html')
    else:
        year = request.form.get('year')
        month = request.form.get('month')
        result = SQLserver.request('1_request.sql', year=year, month=month)

        table = ItemTableRequest1(result)

        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTMLtable == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTMLtable)

        file.write('</div>{% endblock %}')
        file.close()

        return render_template('request_result_child.html', url_back='./request1',
                               title=f'Сотрудники, которые были наняты в месяце - {month}, в году - {year}')


@requests_app.route('/request2', methods=['GET', 'POST'])
@group_permission_decorator
def requests_request2():
    if request.method == 'GET':
        return render_template('request_2.html')
    else:
        hiredDays = request.form.get('hiredDays')
        result = SQLserver.request('2_request.sql', hiredDays=hiredDays)
        table = ItemTableRequest2(result)

        HTMLtable = table.__html__()

        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')


        if HTMLtable == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTMLtable)

        file.write('</div>{% endblock %}')
        file.close()

        return render_template('request_result_child.html', url_back='./request2',
                               title=f'Сотрудники, которых наняли {hiredDays} дней назад')


@requests_app.route('/request3', methods=['GET', 'POST'])
@group_permission_decorator
def requests_request3():
    if request.method == 'GET':
        return render_template('request_3.html')
    else:
        licensePlates = request.form.get('licensePlates')
        result = SQLserver.request('3_request.sql', licensePlates=licensePlates)
        table = ItemTableRequest3(result)

        HTMLtable = table.__html__()

        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTMLtable == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()

        return render_template('request_result_child.html', url_back='./request3',
                               title=f'Машины, где в лицензионном номере есть буквы: {licensePlates}')


@requests_app.route('/request4', methods=['GET', 'POST'])
@group_permission_decorator
def requests_request4():
    if request.method == 'GET':
        return render_template('request_4.html')
    else:
        year = request.form.get('year')
        result = SQLserver.request('4_request.sql', year=year)

        for temp in result:
            temp['MonthNoteDate'] = temp['MONTH(NoteDate)']
            del temp['MONTH(NoteDate)']
        for temp in result:
            temp['countTTN'] = temp['COUNT(idConsignmentNote)']
            del temp['COUNT(idConsignmentNote)']
        table = ItemTableRequest4(result)

        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTMLtable == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTMLtable)

        file.write('</div>{% endblock %}')
        file.close()

        return render_template('request_result_child.html', url_back='./request4',
                               title=f'Количество ТТН, которые оформили в {year} году')


@requests_app.route('/request5', methods=['GET', 'POST'])
@group_permission_decorator
def requests_request5():
    if request.method == 'GET':
        return render_template('request_5.html')
    else:
        year = request.form.get('year')
        result = SQLserver.request('5_request.sql', year=year)

        for temp in result:
            temp['sumWeight'] = temp['SUM(Weight)']
            del temp['SUM(Weight)']
        table = ItemTableRequest5(result)

        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTMLtable == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTMLtable)

        file.write('</div>{% endblock %}')
        file.close()
        return render_template('request_result_child.html', url_back='./request5',
                               title=f'Суммарный вес клиентов за {year} год')


@requests_app.route('/request6', methods=['GET', 'POST'])
@group_permission_decorator
def requests_request6():
    if request.method == 'GET':
        return render_template('request_6.html')
    else:
        year = request.form.get('year')
        result = SQLserver.request('6_request.sql', year=year)

        for temp in result:
            temp['MonthNoteDate'] = temp['MONTH(NoteDate)']
            del temp['MONTH(NoteDate)']
        for temp in result:
            temp['avgWeight'] = temp['AVG(Weight)']
            del temp['AVG(Weight)']
        table = ItemTableRequest6(result)

        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div class="article_3">')

        if HTMLtable == "<p>No Items</p>":
            file.write('<p class="article_2">По данному запросу результатов не найдено</p>')
        else:
            file.write(HTMLtable)

        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html', url_back='./request6',
                               title=f'Средний вес, который перевезли, по месяцем в {year} году')
