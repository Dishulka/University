import pymysql

from sql.SQLconnect import SQLconnect
from sql.SQLprovider import SQLProvider


class SQLmaster:
    def __init__(self, dbconfig):
        self.db_connect = SQLconnect(dbconfig)
        self.db_request = SQLProvider(r'.\sql\requests')  # Сюда путь до папки с запросами

    def request(self, filename, **kwargs) -> dict:
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
        cursor = self.db_connect.cursor
        request = self.db_request.get(filename, **kwargs)
        if cursor is None:
            raise ValueError('Cursor is None')
        elif cursor:
            cursor.execute(request)
            self.db_connect.conn.commit()
            return None
