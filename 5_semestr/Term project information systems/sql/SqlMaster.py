import pymysql

from sql.SqlConnect import SQLConnect
from sql.SqlProvider import SQLProvider


class SQLMaster:
    """
    Класс для взаимодействия с базой данных SQL
    """

    def __init__(self, db_config):
        """
        Конструктор для SQLMaster

        Args:
            db_config: dict. Конфигурация для базы данных SQL
        """
        self.db_connect = SQLConnect(db_config)
        self.db_request = SQLProvider(r'.\sql\requests')

    def request(self, filename, **kwargs):
        """
        Выполняет запрос к базе данных SQL

        Args:
            filename: str. Имя запроса
            kwargs: dict. Параметры запроса

        Returns:
            dict. Результат SQL запроса
        """
        cursor = self.db_connect.cursor
        request = self.db_request.get(filename, **kwargs)
        if cursor is None:
            raise ValueError('Cursor is None')
        elif cursor:
            cursorDict = self.db_connect.conn.cursor(pymysql.cursors.DictCursor)
            cursorDict.execute(request)
            resulting = cursorDict.fetchall()
            return resulting

    def update_insert(self, filename, **kwargs):
        """
        Выполняет update/request/delete в базе данных SQL

        Args:
            filename: str. Имя файла
            kwargs: dict. Параметры запроса

        Returns:
            dict. Результат SQL запроса
        """
        cursor = self.db_connect.cursor
        request = self.db_request.get(filename, **kwargs)
        if cursor is None:
            raise ValueError('Cursor is None')
        elif cursor:
            cursor.execute(request)
            self.db_connect.conn.commit()
            return None
