#include "Figure.h"


Figure::Figure(char* p)
{
	_position[0] = p[0];
	_position[1] = p[1];
}


//Addressing (get position) operator overload 
Figure::operator char* ()
{
	return _position;			//return char*
}


//Comparison (==) operator overload
int Figure::operator== (char* p)
{
	return ((_position[0] == p[0]) && (_position[1] == p[1]));
}


//Assignment operator overload
Figure& Figure::operator=(char* p)
{
	_position[0] = p[0];
	_position[1] = p[1];
	return (*this);
}


//Check position out from the chessboard
int Figure::deskOut(char* p)
{
	return ((p[0] > 'h') || (p[0] < 'a') || (p[1] < '1') || (p[1] > '8'));
}


//Output overload
std::ostream& operator<<(std::ostream& out, Figure& f)
{
	return (out << f.typeFigure() << f._position[0] << f._position[1]);
}


//Input overload
std::istream& operator>>(std::istream& in, Figure& f)
{
	in.unsetf(std::ios::skipws);						//Disables skipws flag in stream: skipping of leading whitespace
	char s[2];
	in >> s[0] >> s[1];
	in.ignore(64, '\n');								//Ignore characters after s[0] and s[1] 
	if ((f.attack(s) == 0) || (f == s))
		in.clear(std::ios::failbit | in.rdstate());		//Sets the stream error state flags by assigning them the value of state
	f = s;
	return in;
}


//Value of [a-h]
char Figure::getX()
{
	return _position[0];
}


//Value of [1-8]
char Figure::getY()
{
	return _position[1];
}


void Figure::accessX(char a)
{
	_position[0] = a;
}


void Figure::accessY(char b)
{
	_position[1] = b;
}


//King attack
int Figure::attack(char* p)
{
	if (deskOut(p) > 0)
		return 0;
	int x = (int)(_position[0] - p[0]);
	int y = _position[1] - p[1];
	if ((x > 0) || (y > 0))
		return 0;
	x *= -1;
	y *= -1;
	if ((x > 1) || (y > 1))
		return 0;
	return 1;
}


//Print chessboards
void Figure::printBoard()
{
	char s[2];
	char ch;
	char* mark = (char*)".x";
	std::cout << "  a b c d e f g h\n";
	for (int i = 8; i > 0; i--)
	{
		std::cout << i << ' ';
		s[1] = '0' + i;
		for (int j = 0; j < 8; j++)
		{
			s[0] = 'a' + j;
			ch = (*this == s) ? typeFigure() : mark[attack(s)];
			std::cout << ch << ' ';
		}
		std::cout << i << '\n';
	}
	std::cout << "  a b c d e f g h\n";
}