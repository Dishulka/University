#include "Gambler.h"
#include <iostream>


int main(int argc, char* argv[])
{
	//Initialization start position
	char* startPos = (char*)"a1";
	char* endPos = (char*)"h8";

	//Init Game
	Figure f(startPos);
	f.printBoard();

	Gambler* players[] = {
		new Man(f, "Man"),
		new Pen(f, "Computer")
	};

	//Start Game
	int i = 1;
	while (f != endPos)
	{
		players[i%2]->query();
		if (!players[i%2]->move())
		{
			std::cout << "Invalid input\n";
			return 0;
		}

		f.printBoard();
		i++;
	}
	std::cout << std::endl << players[(i+1) % 2]->getName()<<" Wins"<<std::endl;
	
	delete players[0];
	delete players[1];
	return 0;
}