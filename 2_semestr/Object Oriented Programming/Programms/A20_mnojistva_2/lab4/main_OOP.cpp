#include <iostream>
using namespace std;


class Alpha
{
private:
	unsigned int bin[2];
public:
	Alpha();
	Alpha(char*);
	int operator, (Alpha&);
	int pop(unsigned);
	operator char*();
};


Alpha::Alpha()
{
	bin[0] = 0;
	bin[1] = 17842449;
}


Alpha::Alpha(char* s)
{
	bin[0] = 0;
	bin[1] = 0;
	while (*s)
	{
		if (*s <= 'Z')
			bin[0] |= (1 << (*s - 'A'));
		else
			bin[1] |= (1 << (*s - 'a'));
		s++;
	}
}


Alpha::operator char* ()
{
	static  char s[64];
	int i = 0, j = 0;
	unsigned  b = this->bin[0];
	while (b > 0)
	{
		if (b & 1)
			s[j++] = 'A' + i;
		i++;
		b >>= 1;
	}
	b = this->bin[1];
	i = 0;
	while (b > 0)
	{
		if (b & 1)
			s[j++] = 'a' + i;
		i++;
		b >>= 1;
	}
	s[j] = 0;
	return (s);
}


int Alpha::operator , (Alpha& a) //вычисление скалярного произведения
{
	return pop(this->bin[1] & a.bin[1]);
}


int Alpha::pop(unsigned x) //быстрый подсчет единичных разрядов
{
	int i = 0;
	while (x != 0)
	{
		x = x & (x - 1);
		i++;
	}
	return i;
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid number of arguments" << endl;
		return (-1);
	}
	Alpha a(argv[1]);
	Alpha b;
	int sum = (a, b);
	cout << "(" << (char*)a << ", ";
	cout << (char*)b << ") =  " << sum << endl;
	return (0);
}