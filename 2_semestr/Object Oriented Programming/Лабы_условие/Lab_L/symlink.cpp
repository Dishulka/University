// _symlink.cpp
// SymLink class and main
/* Разработать ООП для перестановки символов заданной строки в случайном
порядке. Зерно случайной последовательности генератора псевдослучайных
чисел должно передаваться через аргумент командной строки. Исходная строка
должна передаваться программе через поток стандартного ввода. Результирующую
строку образует последовательное перемещение символов из случайно выбранных
позиций строки в ее начало или конец. После каждой такой перестановки
полученная строка должна отображаться через поток стандартного вывода, а
очередной случайно выбранный символ указывается знаком > или < в зависимости
от направления перемещения. Число случайных перестановок равно длине строки.
Разработка программы должна быть основана на использовании абстрактной
структуры двунаправленного связанного списка с реализацией операций просмотра,
удаления и вставки его элементов. Публичные методы должны определить базовый
класс элемента абстрактного списка с защищенными адресными полями данных. Ему
должен наследовать производный класс элемента списка символов с приватным полем
кода символов и публичной перегрузкой базовых методов с адресным возвратом.
Кроме того, в нем должны быть определенны собственные публичные методы. Они
должны обеспечивать стандартный вывод списка символов и адресацию их позиций по
смещению от концов списка. В основной функции программы должна быть реализована
необходимая функциональная обработка списка символов с использованием
динамического распределения памяти для его элементов. */

#include  <cstdio>
#include  <cstdlib>
#include  "dlink.hpp"

using namespace std;

// SymLink class
class SymLink : public Dlink {
private:
  unsigned char _sym;

public:
  SymLink(unsigned char c) : Dlink(), _sym(c) {};
  SymLink* incr() { return (SymLink*)Dlink::incr(); }; // метод базового класса
  SymLink* decr() { return (SymLink*)Dlink::decr(); }; // метод базового класса
  SymLink* seek(int);
  int print();

};

SymLink* SymLink::seek(int n) {
  if (n > 0) {
    return (SymLink* )Dlink::toTail(n);
  }
  if (n < 0) {
    return (SymLink* )Dlink::toHead(abs(n));
  }
  return this;
}

int SymLink::print() {
  SymLink* p = this;
  SymLink* q;
  int n = 0;
  while (p != NULL) {
    putchar(p->_sym);
    q = p->incr();
    p = q;
    n++;
  }
  return n - 2; // учет "стражей" - указателей на начало и конец
}

int main(int argc, char** argv) {
  unsigned seed = 0;
  int count = 0;
  int length;
  int ch;
  unsigned pos;
  int side;
  SymLink* watch[2]; // начало и конец списка
  SymLink* head;
  SymLink* tail;
  SymLink* q;
  SymLink* p;
  Dlink* (Dlink::* insert[])(Dlink*) = { &Dlink::after, &Dlink::before };
  if (argc > 1) {
    seed = atoi(argv[1]);
  }
  watch[0] = head = new SymLink('\n');
  watch[1] = tail = new SymLink('\n');
  tail ->before(head);
  while ((ch = getchar()) != '\n') {
    q = new SymLink(ch);
    tail->before(q);
  }
  if ((length = head->print() - 1) < 2) {
    count = length;
  }
  srand(seed);
  while(count < length) {
    side = rand() % 2; // 0 или 1
    while ((pos = rand() % length) == 0) {}; // sic!
    if (side == 0) {
      printf("%*c\n", pos, '<');
    } else {
      printf("%*c\n", pos, '>');
    }
    q = head->seek(pos);
    q->excluse();
    (watch[side]->*insert[side])(q);
    head->print();
    count++;
  }
  p = tail;
  while (p != NULL) {
    q = p->decr();
    p->excluse();
    delete p;
    p = q;
  }
  return length + 1;
}
