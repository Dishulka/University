#ifndef FIGURE
#define FIGURE

#include <iostream>


class Figure
{
protected:
	char _position[2];													//Position on the chessboard [a-h][1-8]
public:
	Figure() {};
	Figure(char*);
	virtual int attack(char*) = 0;										//Checking if the cell might be at risk
	virtual char typeFigure() = 0;										//Virtual type of figure
	operator char* ();													//Addressing (get position) operator overload 
	int operator==(char*);												//Comparison (==) operator overload
	Figure& operator=(char*);											//Assignment operator overload
	int permutation(char*);												//Permutation the figure on chessboard
	static int deskOut(char*);											//Check position out from the chessboard
	void printBoard();													//Print chessboars
	friend std::ostream& operator<<(std::ostream&, Figure&);			//Output overload
	friend std::istream& operator>>(std::istream&, Figure&);			//Input overload
};


#endif