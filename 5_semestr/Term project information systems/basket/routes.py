import json

from flask import Blueprint, render_template, request, session, redirect, url_for, flash
from flask_table import Col, Table
from flask_table.html import element

from access import group_permission_decorator
from sql.SqlMaster import SQLMaster

basket_app = Blueprint('basket', __name__, template_folder='templates')

SQLServer = SQLMaster(json.load(open('config/configDataBase.json', 'r')))


class ExternalURLCol(Col):
    def __init__(self, name, url_attr, class_attr, **kwargs):
        self.url_attr = url_attr
        self.class_attr = class_attr
        super(ExternalURLCol, self).__init__(name, **kwargs)

    def td_contents(self, item, attr_list):
        text = self.from_attr_list(item, attr_list)
        url = self.from_attr_list(item, [self.url_attr])
        classURL = self.from_attr_list(item, [self.class_attr])
        return element('a', {'href': url, 'class': classURL}, content=text)


class ItemTableBasketGoods(Table):
    Number = Col("№")
    Name = Col('Наименование')
    Weight = Col('Вес')
    DeleteLink = ExternalURLCol(' ', url_attr='urlDelete', attr='nameDelete', class_attr='classDelete')


@basket_app.route('/', methods=['GET', 'POST'])
@group_permission_decorator
def basket_index():
    if request.method == 'GET':
        customers_names = SQLServer.request('basket_get_customers_names.sql')
        employeers_names = SQLServer.request('basket_get_employees_names.sql')
        license_plates = SQLServer.request('basket_get_license_plates.sql')

        return render_template('basket_index.html', customers_names=customers_names, license_plates=license_plates,
                               employeers_names=employeers_names)
    else:
        id_customer = request.form.get('customer_name')
        session['id_customer'] = id_customer

        id_employee = request.form.get('employee_name')
        id_car = request.form.get('license_plate')

        SQLServer.update_insert('basket_insert_consignment_note.sql', idCar=id_car, idEmployee=id_employee,
                                idClient=id_customer)

        id_consignment_note = SQLServer.request('basket_get_id_consigment.sql')[0]['idConsignmentNote']
        session['id_consignment_note'] = id_consignment_note

        return redirect(url_for('basket.basket_goods'))


@basket_app.route('/goods', methods=['GET', 'POST'])
@group_permission_decorator
def basket_goods():
    if session.get('id_customer') == -1:
        return redirect(url_for('basket.basket_index'))

    if request.method == 'GET':
        id_customer = session.get('id_customer')
        id_consignment_note = session.get('id_consignment_note')

        customer_name = SQLServer.request('basket_get_customer_name.sql', idClient=id_customer)[0]['Name']
        weight = SQLServer.request('basket_get_consignment_note_weight.sql', idConsignmentNote=id_consignment_note)[0][
            'Weight']

        result = SQLServer.request('basket_get_goods.sql', idConsignmentNote=id_consignment_note)
        i = 1
        for good in result:
            idGood = good['idGood']
            good['Number'] = i
            i += 1
            good['urlDelete'] = url_for('basket.basket_goods') + f'/delete' + f'/{idGood}'
            good['nameDelete'] = f'Удалить'
            good['classDelete'] = f"confirmable"

        table = ItemTableBasketGoods(result)

        HTML_table = table.__html__()

        file = open(r'.\basket\templates\basket_goods_child.html', 'w', encoding='utf-8')
        file.write('{% extends \'basket_goods_main.html\' %}{% block child %}<div class="article_3">')

        if HTML_table == "<p>No Items</p>":
            file.write('<p class="article_2">Груз отсутствует</p>')
        else:
            file.write(HTML_table)
        file.write('</div>{% endblock %}')
        file.close()

        return render_template('basket_goods_child.html', customer_name=customer_name, Weight=weight)
    else:
        if request.form.get('add_note', -1) == '0':
            name = request.form.get('name')
            weight = request.form.get('weight')

            id_consignment_note = session.get('id_consignment_note')
            weight_note = \
                SQLServer.request('basket_get_consignment_note_weight.sql', idConsignmentNote=id_consignment_note)[0][
                    'Weight']
            SQLServer.update_insert('basket_insert_goods.sql', idConsignmentNote=id_consignment_note, Name=name,
                                    Weight=weight)
            SQLServer.update_insert('basket_update_consignment_note_weight.sql',
                                    idConsignmentNote=id_consignment_note,
                                    weight=int(weight) + weight_note)

        if request.form.get('clear_note', -1) == '0':
            id_consignment_note = session.get('id_consignment_note')

            SQLServer.update_insert('basket_update_consignment_note_weight.sql',
                                    idConsignmentNote=id_consignment_note, weight=0)
            SQLServer.update_insert('basket_clear_goods.sql',
                                    idConsignmentNote=id_consignment_note)

        if request.form.get('confirm_order', -1) == '0':
            count_goods = SQLServer.request('basket_get_count_goods.sql',
                                            idConsignmentNote=session.get('id_consignment_note'))[0]['COUNT(idGood)']
            if count_goods > 0:
                redirect(url_for('basket.basket_finish_order'))
            else:
                flash('Нет товаров в заказе')

        if request.form.get('main_menu', -1) == '0':
            if SQLServer.request('basket_get_count_goods.sql',
                                 idConsignmentNote=session.get('id_consignment_note'))[0]['COUNT(idGood)'] > 0:
                SQLServer.update_insert('basket_delete_goods.sql',
                                        idConsignmentNote=session.get('id_consignment_note'))

            SQLServer.update_insert('basket_delete_consingment_note.sql',
                                    idConsignmentNote=session.get('id_consignment_note'))

            session['id_consignment_note'] = ""
            session['id_customer'] = ""
            return redirect(url_for('index'))

        return redirect(url_for('basket.basket_goods'))


@basket_app.route('/goods/delete/<id_good>')
@group_permission_decorator
def basket_delete_good(id_good):
    id_consignment_note = session.get('id_consignment_note')

    weight = SQLServer.request('basket_get_good_weight.sql', idGood=id_good)[0]['Weight']
    weight_note = \
        SQLServer.request('basket_get_consignment_note_weight.sql', idConsignmentNote=id_consignment_note)[0]['Weight']
    SQLServer.update_insert('basket_update_consignment_note_weight.sql',
                            idConsignmentNote=id_consignment_note,
                            weight=int(weight_note) - int(weight))

    SQLServer.update_insert('basket_delete_good.sql', idGood=id_good)
    return redirect(url_for('basket.basket_goods'))


@basket_app.route('/finish')
@group_permission_decorator
def basket_finish_order():
    id_customer = session.get('id_customer')
    id_consignment_note = session.get('id_consignment_note')

    weight = SQLServer.request('basket_get_consignment_note_weight.sql', idConsignmentNote=id_consignment_note)[0][
        'Weight']
    weight_customer = SQLServer.request('basket_get_customer_weight.sql', idClient=id_customer)[0]['TotalWeight']

    SQLServer.update_insert('basket_update_customer_info.sql',
                            idClient=id_customer,
                            weight=weight + weight_customer)

    session['id_customer'] = -1
    return render_template('basket_finish_order.html')
