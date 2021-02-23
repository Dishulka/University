#ifndef GAME
#define GAME

#include <iostream>
#include "Figure.h"

class Game
{
protected:
	Figure* _figure;			//Pointer at figure
	const char* _name;			//Name of player
public:
	Game(Figure& f)
	{
		_figure = &f;
	};
	virtual int move() = 0;							//Virtual function of move players
	~Game() {};
};

class Player : public Game
{
public:
	Player(Figure& f, const char* name) : Game(f) { _name = name; };
	virtual int move();
};


class Computer : public Game
{
public:
	Computer(Figure& f, const char* name) : Game(f) { _name = name; };
	virtual int move();
};



#endif
