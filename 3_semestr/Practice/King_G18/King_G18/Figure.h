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
	int attack(char*);													//Checking if the cell might be at risk
	char typeFigure() { return 'K'; };									//Virtual type of figure
	void printBoard();													//Print chessboars
	char getX();															//Get position on chessboard [a-h]
	char getY();															//Get position on chessboard [a-h]
	void accessX(char x);												//Assigns a value to one of the cell values
	void accessY(char y);												//Assigns a value to one of the cell values
	static int deskOut(char*);											//Check position out from the chessboard
	Figure& operator=(char*);											//Assignment operator overload
	operator char* ();													//Addressing (get position) operator overload 
	int operator==(char*);												//Comparison (==) operator overload
	friend std::ostream& operator<<(std::ostream&, Figure&);			//Output overload
	friend std::istream& operator>>(std::istream&, Figure&);			//Input overload
};


#endif