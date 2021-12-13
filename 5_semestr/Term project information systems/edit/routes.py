import json

from flask import Blueprint, render_template, url_for, request
from flask_table import Table, Col
from flask_table.html import element
from django.utils.html import escape

from access import group_permission_decorator
from sql.SqlMaster import SQLMaster

edit_app = Blueprint('edit', __name__, template_folder='templates')

SQLServer = SQLMaster(json.load(open('config/configDataBase.json', 'r')))


class ExternalURLCol(Col):
    """
    Класс для использования ссылок
    """

    def __init__(self, name, url_attr, class_attr, **kwargs):
        """
        Конструктор для ExternalURLCol

        Args:
            name: str. Имя столбца
            url_attr: str. URL для ссылки
            class_attr: str. Имя класса
            kwargs: dict. Дополнительные параметры
        """
        self.url_attr = url_attr
        self.class_attr = class_attr
        super(ExternalURLCol, self).__init__(name, **kwargs)

    def td_contents(self, item, attr_list):
        """
        Генерирует таблицу

        Args:
            item: dict. Параметры для строки
            attr_list: list. Имя ссылки

        Returns:
             Эелемент в таблице
        """
        text = self.from_attr_list(item, attr_list)
        url = self.from_attr_list(item, [self.url_attr])
        classURL = self.from_attr_list(item, [self.class_attr])
        return element('a', {'href': url, 'class': classURL}, content=text)


class ItemTableEditUser(Table):
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
    result = SQLServer.request('edit_users_info.sql')
    for user in result:
        id_group = user['idGroup']
        user['urlUpdate'] = url_for('edit.edit_users') + f'/{id_group}'
        user['nameUpdate'] = f'Редактировать'
        user['classUpdate'] = f""
        user['urlDelete'] = url_for('edit.edit_users') + f'/delete' + f'/{id_group}'
        user['nameDelete'] = f'Удалить'
        user['classDelete'] = f"confirmable"
    table = ItemTableEditUser(result)

    HTML_table = table.__html__()
    file = open(r'.\edit\templates\edit_child.html', 'w', encoding='utf-8')
    file.write('{% extends \'edit_base.html\' %}{% block child %}<div class="article_3">')
    file.write(HTML_table)
    file.write('</div>{% endblock %}')
    file.close()

    return render_template('edit_child.html', title="Все пользователи",
                           url_for_insert=url_for('edit.edit_insert_user'), insert_title="Добавить пользователя")


@edit_app.route('/users/<user>', methods=['GET', 'POST'])
@group_permission_decorator
def edit_user(user):
    if request.method == 'GET':
        result = SQLServer.request('edit_get_user.sql', id=user)[0]
        return render_template('edit_user.html', id_group=result['idGroup'], login=result['Login'],
                               password=result['Password'], accessLevel=result['AccessLevel'])
    else:
        id_group = user
        login = request.form.get('login')
        password = request.form.get('password')
        access_level = request.form.get('access_level')
        SQLServer.update_insert('edit_update_user.sql', idGroup=id_group, Login=login, Password=password,
                                AccessLevel=access_level)
        return render_template('edit_result_user.html')


@edit_app.route('/users/add', methods=['GET', 'POST'])
@group_permission_decorator
def edit_insert_user():
    if request.method == 'GET':
        return render_template('edit_insert_user.html')
    else:
        login = request.form.get('login')
        password = request.form.get('password')
        access_level = request.form.get('access_level')
        SQLServer.update_insert('edit_insert_user.sql', Login=login, Password=password,
                                AccessLevel=access_level)
        return render_template('edit_result_user.html')


@edit_app.route('/users/delete/<user>')
@group_permission_decorator
def edit_delete_user(user):
    SQLServer.update_insert('edit_delete_user.sql', idGroup=user)
    return render_template('edit_delete_user.html', idGroup=user)


@edit_app.route('/customers')
@group_permission_decorator
def edit_customers():
    result = SQLServer.request('edit_customer_info.sql')
    for customer in result:
        id_client = customer['idClient']
        customer['urlUpdate'] = url_for('edit.edit_customers') + f'/{id_client}'
        customer['nameUpdate'] = f'Редактировать'
        customer['classUpdate'] = f""
        customer['urlDelete'] = url_for('edit.edit_customers') + f'/delete' + f'/{id_client}'
        customer['nameDelete'] = f'Удалить'
        customer['classDelete'] = f"confirmable"
    table = ItemTableEditCustomer(result)

    HTML_table = table.__html__()
    file = open(r'.\edit\templates\edit_child.html', 'w', encoding='utf-8')
    file.write('{% extends \'edit_base.html\' %}{% block child %}<div class="article_3">')
    file.write(HTML_table)
    file.write('</div>{% endblock %}')
    file.close()

    return render_template('edit_child.html', title="Все заказчики",
                           url_for_insert=url_for('edit.edit_insert_customer'), insert_title="Добавить заказчика")


@edit_app.route('/customers/<customer>', methods=['GET', 'POST'])
@group_permission_decorator
def edit_customer(customer):
    if request.method == 'GET':
        result = SQLServer.request('get_customer.sql', id=customer)[0]
        a=escape(result['Adress'])
        return render_template('edit_customer.html', id_client=result['idClient'], name=result['Name'],
                               adress=result['Adress'], total_weight=result['TotalWeight'],
                               date_total_weight=result['DateTotalWeight'])
    else:
        id_client = customer
        name = request.form.get('name')
        adress = request.form.get('adress')
        total_weight = request.form.get('total_weight')
        date_total_weight = request.form.get('date_total_weight')

        SQLServer.update_insert('edit_update_customer.sql', idClient=id_client, Name=name, Adress=adress,
                                TotalWeight=total_weight, DateTotalWeight=date_total_weight)
        return render_template('edit_result_customer.html')


@edit_app.route('/customers/add', methods=['GET', 'POST'])
@group_permission_decorator
def edit_insert_customer():
    if request.method == 'GET':
        return render_template('edit_insert_customer.html')
    else:
        name = request.form.get('name')
        adress = request.form.get('adress')
        total_weight = request.form.get('total_weight')
        date_total_weight = request.form.get('date_total_weight')

        SQLServer.update_insert('edit_insert_customer.sql', Name=name, Adress=adress,
                                TotalWeight=total_weight, DateTotalWeight=date_total_weight)
        return render_template('edit_result_customer.html')


@edit_app.route('/customers/delete/<customer>')
@group_permission_decorator
def edit_delete_customer(customer):
    SQLServer.update_insert('edit_delete_customer.sql', idClient=customer)
    return render_template('edit_delete_customer.html', idClient=customer)
