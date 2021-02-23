#include <iostream>
#include <cctype>
using namespace std;


class Alpha {
private:
	unsigned int bin;
public:
	Alpha() { bin = 0; };
	Alpha(char*);
	Alpha operator ^(Alpha&);
	Alpha operator ~();
	friend ostream& operator << (ostream&, Alpha&);
};


Alpha::Alpha(char* s)
{
	bin = 0;
	while (*s)
	{
		if (((*s >= 'A') && (*s <= 'Z')) || ((*s >= 'a') && (*s <= 'z')))
		{
			bin |= (1 << (tolower(*s) - 'a'));
		}
		s++;
	}
}


Alpha Alpha::operator ^ (Alpha& a)
{
	Alpha z;
	z.bin = this->bin ^ a.bin;
	return(z);
}


Alpha Alpha::operator ~ ()
{
	Alpha z;
	z.bin = (~(this->bin));
	return(z);
}


ostream& operator << (ostream& out, Alpha& a)
{
	unsigned  bit = 33554432;
	for (int i = 25; i >= 0; i--)
	{
		if ((a.bin & bit) > 0)
			out << (char)('a' + i);
		bit = bit >> 1;
	}
	return out;
}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid number of arguments" << endl;
		return -1;
	}
	Alpha x(argv[1]);
	Alpha y(argv[2]);
	Alpha z;
	z = x ^ y;
	z = ~z;
	cout << z << endl;
	return 0;
}