/*
  Демонстрация работы с потоковыми классами ввода-вывода в C++
  Козов А.В., каф. РК-6, МГТУ им. Н.Э. Баумана
*/

#include <iostream>
#include <unistd.h>

// Класс шкалы-индикатора
class ProgressBar {
protected:
  int _l;           // ширина строки вывода
  char _p;          // символ-заполнитель
  char _s;          // пробельный заполнитель
  std::ostream& _o; // ссылка на потоковый объект для вывода

public:
  // Конструктор, принимает ссылку на потоковый объект для вывода и три необязательных параметра:
  // p - символ-заполнитель
  // s - символ для незаполненной части шкалы
  // l - длина строки
  ProgressBar(std::ostream& f, char p = '#', char s = ' ', int l = 80) : _l(l), _p(p), _s(s), _o(f) {
    if (_l < 10) {
      _l = 10;
    }
  };
  // Метод для вывода индикатора, принимает значение от 0 до 1 для отображения шкалы
  void plot(float rate) {
    // проверка допустимости значения
    if (rate < 0 || rate > 1) {
      return;
    }
    _o.setf(std::ios::left);    // установка выравнивания
    _o << "\r[";                // сброс текущей позиции
    // вывод необходимого числа символов-заполнителей
    for (int i = 0; i < (_l - 7)*rate; i++) {
      _o << _p;
    }
    _o.setf(std::ios::right);         // установка выравнивания
    _o.width(_l - (_l - 7)*rate - 6); // установка ширины поля вывода
    _o.fill(_s);                      // пробельный заполнитель
    _o << "]";
    _o.width(4); // установка ширины поля вывода
    _o.fill(' '); // пробельный заполнитель перед числом
    _o << int(100 * rate) << "%" << std::flush;  // вывод целочисленного значения
  }
};

// Основная функция для тестирования
int main(int argc, char const **argv) {
  ProgressBar p(std::cout, '%', '~', 60);
  for (int i = 0; i <= 510; i++) {
    p.plot(i/510.0);
    usleep(25*1E3);
  }
  std::cout << std::endl;
  return 0;
}
