// chesslib cpp file

#include "chesslib.hpp"

// функция проверки позиции для Plus
int Plus::attack(char* p) {
  if (deskout(p) > 0) {
    return 0;
  }
  int x = p[0] - _position[0];
  int y = p[1] - _position[1];
  if (x < 0) {
    x = -x;
  }
  if (y < 0) {
    y = -y;
  }
  if ((x + y) < 2) {
    return 1;
  }
  return 0;
}

// функция проверки позиции для Cros
int Cros::attack(char* p) {
  if (deskout(p) > 0) {
    return 0;
  }
  int x = p[0] - _position[0];
  int y = p[1] - _position[1];
  if (x < 0) {
    x = -x;
  }
  if (y < 0) {
    y = -y;
  }
  if ((x != y) || ((x + y) > 2)) {
    return 0;
  }
  return 2;
}

// функция проверки позиции для Star
int Star::attack(char* s) {
  if (Plus::attack(s) > 0)
    return 1;
  if (Cros::attack(s) > 0)
    return 2;
  return 0;
}
