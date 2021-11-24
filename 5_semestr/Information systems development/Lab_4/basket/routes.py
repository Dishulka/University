import json

from flask import Blueprint, request, session, render_template, redirect

from access import group_permission_decorator
from sql.SQLmaster import SQLmaster

basket_app = Blueprint('basket', __name__, template_folder='templates')
SQLserver = SQLmaster(json.load(open('config/configDataBase.json', 'r')))


@basket_app.route('/', methods=['GET', 'POST'])
@group_permission_decorator
def basket_index():
    if request.method == 'GET':
        services = SQLserver.request('basket_services.sql')
        basketId = session.get('basket', [])
        basket = []
        for id in basketId:
            basket.append(SQLserver.request('basket_get_service.sql', idService=int(id))[0])
            for i in range(len(services)):
                cur = basket[len(basket) - 1]
                test = services[i]
                if cur['idService'] == test['idService']:
                    services.pop(i)
                    break
        return render_template('basket_index.html', services=services, basket=basket)
    else:
        if request.form['WhatRow'] == 'Add':
            idService = request.form['idService']
            b = session.get('basket', [])
            if b is None:
                b = []
            b.append(idService)
            session['basket'] = b
            return redirect('/basket')
        elif request.form['WhatRow'] == 'Buy':
            if 'basket' in session:
                name = request.form.get('name')
                info = request.form.get('info')

                totalSum = 0
                for idService in session['basket']:
                    totalSum += SQLserver.request('basket_get_cost.sql', idService=int(idService))[0]['CostPerUnit']

                SQLserver.update_insert('basket_insert_order.sql', NameCustomer=name, ContactInfo=info,
                                        TotalCost=totalSum)

                last_order = SQLserver.request('basket_get_last_order.sql')[0]['idOrder']
                for idService in session['basket']:
                    SQLserver.update_insert('basket_insert_services_in_order.sql', idService=int(idService),
                                            idOrder=last_order,
                                            Cost=SQLserver.request('basket_get_cost.sql', idService=int(idService))[0][
                                                'CostPerUnit'])

                session.pop('basket')
                return render_template('basket_result.html')
            else:
                redirect('/basket')

            return redirect('/basket')


@basket_app.route('/clear-basket')
@group_permission_decorator
def clear_basket():
    if 'basket' in session:
        session.pop('basket')
    return redirect('/basket')
