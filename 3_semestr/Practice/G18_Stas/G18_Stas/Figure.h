#ifndef FIGUREH
#define FIGUREH
#include <iostream>
#include <string.h>
class Figure
{
protected:
	char _position[2];
public:
	Figure(const char*);
	Figure();

	char getAlp();
	char getNum();

	char isA();
	int attack(char*);
	static int deskOut(char*);
	void printBoard();
	Figure& operator=(char*);
	int operator!=(char*);
	int operator==(char*);
	friend std::ostream& operator<<(std::ostream&, Figure&);
};

#endif 