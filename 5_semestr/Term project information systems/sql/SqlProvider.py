import os
from string import Template


class SQLProvider:
    """
    Класс для создания SQL запросов
    """

    def __init__(self, file_path):
        """
        Конструктор для SQLProvider

        Args:
            file_path: str. Путь к файлу
        """
        self._scripts = {}

        for file in os.listdir(file_path):
            _, expression = os.path.splitext(file)
            if expression == '.sql':
                self._scripts[file] = Template(open(f'{file_path}/{file}', 'r').read())

    def get(self, file_name, **kwargs):
        """
        Создаёт  SQL запрос

        Args:
            file_name: str. Имя файла
            kwargs: dict. Параметры запроса

        Returns:
            str. Параметризованый запрос
        """
        return self._scripts[file_name].substitute(**kwargs)
