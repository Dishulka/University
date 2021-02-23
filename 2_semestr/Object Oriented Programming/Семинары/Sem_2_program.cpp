// Point distance example

#include <stdio.h>
#include <math.h>

class Point2 {
private:
  int _x;
  int _y;
public:
  Point2(int x, int y) : _x(x), _y(y) {};
  int getX() { return _x; };
  int getY() { return _y; };
  friend double distance(Point2*, Point2*);
};

double distance(Point2* r, Point2* q) {
  double d2 = (r->_x - q->_x) * (r->_x - q->_x) + (r->_y - q->_y) * (r->_y - q->_y);
  return sqrt(d2);
};

int main(int argc, char* argv[]) {
  double sum;
  Point2** p;
  Point2* t;
  int x, y;
  int i = 0;
  int j = 0;
  if(argc < 2) {
    return -1;
  }
  p = new Point2*[argc];
  while (++i < argc) {
    sscanf(argv[i], "(%d%*c%d)", &x, &y);
    p[j] = new Point2(x,y);
    j++;
  }
  p[j] = NULL;
  for (i = 0; p[i] != NULL;  i++) {
    sum = 0.0;
    t = p[i];
    for (j = 0; p[j] != NULL;  j++) {
      sum += distance(t, p[j]);
    }
    printf("Dcp(%d; %d) = %f\n", t->getX(), t->getY(), sum / (argc - 2));
  }

  for(j = 0; p[j] != NULL; j++) {
    delete p[j];
  }
  delete[] p;
  return 0;
};
