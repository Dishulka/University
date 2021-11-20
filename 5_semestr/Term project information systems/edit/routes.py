import json
from flask import Blueprint, render_template, url_for, request
from flask_table import Table, Col
from flask_table.html import element
from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

edit_app = Blueprint('edit', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/configDataBase.json', 'r')))

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


class ItemTableEditUsers(Table):
    idGroup = Col('id')
    Login = Col('Логин')
    Password = Col('Пароль')
    AccessLevel = Col('Уровень доступа')
    UpdateLink = ExternalURLCol(' ', url_attr='urlUpdate', attr='nameUpdate', class_attr='classUpdate')
    DeleteLink = ExternalURLCol(' ', url_attr='urlDelete', attr='nameDelete', class_attr='classDelete')


class ItemTableEditCustomer(Table):
    idClient = Col('id')
    Name = Col('Имя')
    Adress = Col('Адрес')
    TotalWeight = Col('Суммарный вес')
    DateTotalWeight = Col('Дата выставления веса')
    UpdateLink = ExternalURLCol(' ', url_attr='urlUpdate', attr='nameUpdate', class_attr='classUpdate')
    DeleteLink = ExternalURLCol(' ', url_attr='urlDelete', attr='nameDelete', class_attr='classDelete')


@edit_app.route('/')
@group_permission_decorator
def edit_index():
    return render_template('edit_index.html')


@edit_app.route('/users')
@group_permission_decorator
def edit_users():
    result = SQLserver.request('reqUsersInfo.sql')
    for user in result:
        idGroup = user['idGroup']
        user['urlUpdate'] = url_for('edit.edit_users') + f'/{idGroup}'
        user['nameUpdate'] = f'Редактировать'
        user['classUpdate'] = f""
        user['urlDelete'] = url_for('edit.edit_users') + f'/delete' + f'/{idGroup}'
        user['nameDelete'] = f'Удалить'
        user['classDelete'] = f"confirmable"
    table = ItemTableEditUsers(result)

    HTMLtable = table.__html__()
    file = open(r'.\edit\templates\edit_child.html', 'w', encoding='utf-8')
    file.write('{% extends \'edit_base.html\' %}{% block child %}<div class="article_3">')
    file.write(HTMLtable)
    file.write('</div>{% endblock %}')
    file.close()

    return render_template('edit_child.html', title="Все пользователи",
                           url_for_insert=url_for('edit.edit_insert_user'), insertTitle="Добавить пользователя")


@edit_app.route('/users/<user>', methods=['GET', 'POST'])
@group_permission_decorator
def edit_user(user):
    if request.method == 'GET':
        result = SQLserver.request('reqGetUser.sql', id=user)[0]
        return render_template('edit_user.html', idGroup=result['idGroup'], Login=result['Login'],
                               Password=result['Password'], AccessLevel=result['AccessLevel'])
    else:
        idGroup = int(user)
        Login = request.form.get('Login')
        Password = request.form.get('Password')
        AccessLevel = int(request.form.get('AccessLevel'))
        SQLserver.update_insert('reqUpdateUser.sql', idGroup=idGroup, Login=Login, Password=Password,
                                AccessLevel=AccessLevel)
        return render_template('edit_result_user.html')


@edit_app.route('/users/add', methods=['GET', 'POST'])
@group_permission_decorator
def edit_insert_user():
    if request.method == 'GET':
        return render_template('edit_insert_user.html')
    else:
        Login = request.form.get('Login')
        Password = request.form.get('Password')
        AccessLevel = int(request.form.get('AccessLevel'))
        SQLserver.update_insert('reqInsertUser.sql', Login=Login, Password=Password,
                                AccessLevel=AccessLevel)
        return render_template('edit_result_user.html')


@edit_app.route('/users/delete/<user>')
@group_permission_decorator
def edit_delete_user(user):
    SQLserver.update_insert('reqDeleteUser.sql', idGroup=int(user))
    return render_template('edit_delete_user.html', idGroup=int(user))


@edit_app.route('/customers')
@group_permission_decorator
def edit_customers():
    result = SQLserver.request('reqCustomerInfo.sql')
    for customer in result:
        idClient = customer['idClient']
        customer['urlUpdate'] = url_for('edit.edit_customers') + f'/{idClient}'
        customer['nameUpdate'] = f'Редактировать'
        customer['classUpdate'] = f""
        customer['urlDelete'] = url_for('edit.edit_customers') + f'/delete' + f'/{idClient}'
        customer['nameDelete'] = f'Удалить'
        customer['classDelete'] = f"confirmable"
    table = ItemTableEditCustomer(result)

    HTMLtable = table.__html__()
    file = open(r'.\edit\templates\edit_child.html', 'w', encoding='utf-8')
    file.write('{% extends \'edit_base.html\' %}{% block child %}<div class="article_3">')
    file.write(HTMLtable)
    file.write('</div>{% endblock %}')
    file.close()

    return render_template('edit_child.html', title="Все заказчики",
                           url_for_insert=url_for('edit.edit_insert_customer'), insertTitle="Добавить заказчика")



@edit_app.route('/customers/<customer>', methods=['GET', 'POST'])
@group_permission_decorator
def edit_customer(customer):
    if request.method == 'GET':
        result = SQLserver.request('reqGetCustomer.sql', id=customer)[0]
        return render_template('edit_customer.html', idClient=result['idClient'], Name=result['Name'],
                               Adress=result['Adress'], TotalWeight=result['TotalWeight'],
                               DateTotalWeight=result['DateTotalWeight'])
    else:
        idClient = int(customer)
        Name = request.form.get('Name')
        Adress = request.form.get('Adress')
        TotalWeight = int(request.form.get('TotalWeight'))
        DateTotalWeight = request.form.get('DateTotalWeight')

        SQLserver.update_insert('reqUpdateCustomer.sql', idClient=idClient, Name=Name, Adress=Adress,
                                TotalWeight=TotalWeight, DateTotalWeight=DateTotalWeight)
        return render_template('edit_result_customer.html')


@edit_app.route('/customers/add', methods=['GET', 'POST'])
@group_permission_decorator
def edit_insert_customer():
    if request.method == 'GET':
        return render_template('edit_insert_customer.html')
    else:
        Name = request.form.get('Name')
        Adress = request.form.get('Adress')
        TotalWeight = request.form.get('TotalWeight')
        DateTotalWeight = request.form.get('DateTotalWeight')

        SQLserver.update_insert('reqInsertCustomer.sql', Name=Name, Adress=Adress,
                                TotalWeight=TotalWeight, DateTotalWeight=DateTotalWeight)
        return render_template('edit_result_customer.html')


@edit_app.route('/customers/delete/<customer>')
@group_permission_decorator
def edit_delete_customer(customer):
    SQLserver.update_insert('reqDeleteCustomer.sql', idClient=int(customer))
    return render_template('edit_delete_customer.html', idClient=int(customer))
