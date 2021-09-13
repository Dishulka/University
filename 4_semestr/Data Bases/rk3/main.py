from db import UserDatabase
from pymysql.err import ProgrammingError
from pymysql.err import OperationalError


# серым подсвечивается то, что не используется
# хинты - подсказывают, что предствляет собой список


def work_with_db(dbconfig, _SQL, schema):
    with UserDatabase(dbconfig) as cursor:
        if cursor is None:
            raise ValueError('Курсор не был создан')
        elif cursor:
            cursor.execute(_SQL)
            result = []
            for str in cursor.fetchall():
                result.append(dict(zip(schema, str)))
            print(result)


if __name__ == '__main__':
    dbconfig = {'host': 'localhost', 'port': 3306, 'user': 'root', 'password':"dish0311", 'db': 'labs'}
    _SQL = """ SELECT * FROM car"""
    schema = ['idCar', 'Brand']
    work_with_db(dbconfig, _SQL, schema)


