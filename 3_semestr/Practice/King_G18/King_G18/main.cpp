#include <iostream>
#include "Figure.h"
#include "Game.h"


int main()
{
	Figure f((char*)"a1");
	
	Game* player[] = { new Player(f, "Player"), new Computer(f, "Computer") };
	f.printBoard();

	int i = 1;
	while ((f.getX() != 'h') && (f.getY() != '8'))
	{
		std::cout << f << '-' << f.typeFigure();

		Figure f_temp;
		std::cin >> f_temp;
		if (f_temp.deskOut((char*)f_temp))
			return -1;

		char a, b;
		a = f_temp.getX();
		b = f_temp.getY();

		int res;
		res = player[i]->move(a, b);
		if (res == 0)
			return -1;

		f.printBoard();
		i++;
		if (i > 1)
			i = 0;
	}

	delete player[0];
	delete player[1];
	return 0;
}