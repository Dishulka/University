#include <iostream>
#include "Game.h"


int Player::move()
{
	char x = x - _figure->getX();
	char y = y - _figure->getY();
	if ((x == 1) && (y == 0))
	{
		char s[2];
		s[0] = x + _figure->getX();
		s[1] = y + _figure->getY();
		_figure->accessX(s[0]);
		_figure->accessY(s[1]);
		return 1;
	}
	if ((x == 1) && (y == 1))
	{
		char s[2];
		s[0] = x + _figure->getX();
		s[1] = y + _figure->getY();
		_figure->accessX(s[0]);
		_figure->accessY(s[1]);
		return 1;
	}
	if ((x == 0) && (y == 1))
	{
		char s[2];
		s[0] = x + _figure->getX();
		s[1] = y + _figure->getY();
		_figure->accessX(s[0]);
		_figure->accessY(s[1]);
		return 1;
	}
	return 0;
}


int Computer::move()
{
	char x = _figure->getX();
	char y = _figure->getY();
	if (x % 2 != 0)
		x += 1;
	if (y % 2 != 0)
		y += 1;
	_figure->accessX((char)x);
	_figure->accessY((char)y);
	std::cout << (char)x << (char)y << std::endl;
	return 1;
}