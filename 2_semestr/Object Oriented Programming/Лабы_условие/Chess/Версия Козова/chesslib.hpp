// chesslib header file

#ifndef CHESSLIB
#define CHESSLIB

#include "figure.hpp"

// фигура Plus
class Plus : virtual public Figure {
public:
  Plus(char* p) : Figure(p) {}; // конструктор
  char isA() { return 'P'; };   // перегрузка метода
  int attack(char*);            // перегрузка метода
};

// фигура Cros
class Cros : virtual public Figure {
public:
  Cros(char* p) : Figure(p) {}; // конструктор
  char isA() { return 'C'; };   // перегрузка метода
  int attack(char*);            // перегрузка метода
};

// фигура Star, наследующая Plus и Cros
class Star : public Plus, public Cros {
public:
  Star(char* p) : Plus(p), Cros(p), Figure(p) {}; // конструктор
  char isA() { return 'S'; };          // перегрузка метода
  int attack(char*);                   // перегрузка метода
};

#endif
