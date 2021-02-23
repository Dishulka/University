#ifndef  CHESSLIB
#define CHESSLIB

#include "Figure.h"


class Queen : virtual public Figure
{
public:
	Queen(char* p) : Figure(p) {};
	Queen() {};
	char typeFigure() { return 'Q'; };
	int attack(char*);
};


class Zebra : virtual public Figure
{
public:
	Zebra(char* p) : Figure(p) {};
	Zebra() {};
	char typeFigure() { return 'Z'; };
	int attack(char*);
};


class Empress : public Queen, public Zebra
{
public:
	Empress(char* p) : Figure(p) {};
	char typeFigure() { return 'E'; };
	int attack(char*);
};


#endif
