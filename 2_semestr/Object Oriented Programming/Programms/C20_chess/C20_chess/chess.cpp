#include <iostream>
#include "chesslib.h"


int main(int argc, char* argv[])
{
	if (argc < 2)
		argv[1] = (char*)("nil");

	if (Figure::deskOut(argv[1]))
	{
		std::cout << "Incorrect position on chessboard." << std::endl;
		std::cout << "Correct " << " to " << (argv[1] = (char*)"a1") << std::endl;
	}

	Empress f(argv[1]);
	do
	{
		f.printBoard();
		std::cout << f << '-' << f.typeFigure();
	} while (std::cin >> f);
	return 0;
}