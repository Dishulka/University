#include "chesslib.h"


//Queen attack square *p
int Queen::attack(char* p)
{
	if (deskOut(p) > 0)
		return 0;
	if ((_position[0] == p[0]) || (_position[1] == p[1]))
		return 1;
	int x = (int)(_position[0] - p[0]);
	int y = _position[1] - p[1];
	if (x < 0)
		x *= (-1);
	if (y < 0)
		y *= (-1);
	if ((x - y) == 0)
		return 1;
	return 0;
}


//Zebra attack square *p
int Zebra::attack(char* p)
{
	if (deskOut(p) > 0)
		return 0;
	int x = _position[0] - p[0];
	int y = _position[1] - p[1];
	if (x < 0)
		x *= (-1);
	if (y < 0)
		y *= (-1);
	if (((x == 3) && (y == 2)) || ((x == 2) && (y == 3)))
		return 2;
	return 0;
}


//Empress attack square *p
int Empress::attack(char* p)
{
	if (Queen::attack(p) > 0)
		return 1;
	if (Zebra::attack(p) > 0)
		return 2;
	return 0;
}