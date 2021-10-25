import json
from flask import Blueprint, render_template, request
from flask_table import Table, Col
from sql.SQLmaster import SQLmaster

requests_app = Blueprint('requests', __name__, template_folder='templates')

SQLserver = SQLmaster(json.load(open('sql/configDataBase.json', 'r')))


class ItemTableRequest1(Table):
    Surname = Col('Surname')
    Position = Col('Position')


class ItemTableRequest2(Table):
    idEmployee = Col('idEmployee')
    Surname = Col('Surname')
    Section = Col('Section')
    HiredDate = Col('HiredDate')
    FiredDate = Col('FiredDate')
    Birthday = Col('Birthday')
    Position = Col('Position')


class ItemTableRequest3(Table):
    idCar = Col('idCar')
    Brand = Col('Brand')
    CarYear = Col('CarYear')
    LicensePlateNumber = Col('LicensePlateNumber')


class ItemTableRequest4(Table):
    MonthNoteDate = Col('MonthNoteDate')
    countTTN = Col('countTTN')


class ItemTableRequest5(Table):
    idClient = Col('idClient')
    sumWeight = Col('sumWeight')


class ItemTableRequest6(Table):
    MonthNoteDate = Col('MonthNoteDate')
    avgWeight = Col('avgWeight')


@requests_app.route('/')
def requests_index():
    return render_template('request_index.html')


@requests_app.route('/request1', methods=['GET', 'POST'])
def requests_request1():
    if request.method == 'GET':
        return render_template('request_1.html')
    else:
        year = request.form.get('year')
        month = request.form.get('month')
        result = SQLserver.request('1_request.sql', year=year, month=month)
        table = ItemTableRequest1(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div>')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
        return render_template('request_result_child.html')


@requests_app.route('/request2', methods=['GET', 'POST'])
def requests_request2():
    if request.method == 'GET':
        return render_template('request_2.html')
    else:
        hiredDays = request.form.get('hiredDays')
        result = SQLserver.request('2_request.sql', hiredDays=hiredDays)
        table = ItemTableRequest2(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div>')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')


@requests_app.route('/request3', methods=['GET', 'POST'])
def requests_request3():
    if request.method == 'GET':
        return render_template('request_3.html')
    else:
        licensePlates = request.form.get('licensePlates')
        result = SQLserver.request('3_request.sql', licensePlates=licensePlates)
        table = ItemTableRequest3(result)
        HTMLtable = table.__html__()
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div>')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')


@requests_app.route('/request4', methods=['GET', 'POST'])
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
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div>')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')


@requests_app.route('/request5', methods=['GET', 'POST'])
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
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div>')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')


@requests_app.route('/request6', methods=['GET', 'POST'])
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
        file = open(r'.\requests\templates\request_result_child.html', 'w')
        file.write('{% extends \'request_result_main.html\' %}{% block child %}<div>')
        file.write(HTMLtable)
        file.write('</div>{% endblock %}')
        file.close()
    return render_template('request_result_child.html')
