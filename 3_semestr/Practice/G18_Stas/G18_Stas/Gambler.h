#ifndef GAMBLERH
#define GAMBLERH

#include "Figure.h"
#include <iostream>
class Gambler
{
protected:
	Figure* _figure;
	const char* _name;
public:
	const char* getName();
	Gambler(Figure&);
	void query();
	virtual bool move() = 0;
};

class Man : public Gambler
{
public:
	Man(Figure&, const char*);
	virtual bool move();
};

class Pen : public Gambler
{
public:
	Pen(Figure&, const char*);
	virtual bool move();
};

#endif