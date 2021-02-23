#pragma warning(disable : 4996)

#include <string.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
using namespace std;


class Fraction 
{
private:
	int _numerator;			//numerator of fraction
	int _denominator;		//denominator of fraction
public:
	Fraction(int nomerator = 0, int denominator = 1) : _numerator(nomerator), _denominator(denominator) {};
	Fraction(char* s);
	void reduce();										//reduce fraction
	operator char*();									//type conversion overload
	int getDenominator() { return _denominator; };
	friend bool operator<(int n, Fraction& f);			//comparison overload '<'
	friend bool operator>(int n, Fraction& f);			//comparison overload '>'
};


Fraction::Fraction(char* s)
{
	char* p = strchr(s, '/');
	_denominator = 1;
	if (p != NULL)
	{
		*p = '\0';
		p++;
		_denominator = atoi(p);
	}
	_numerator = atoi(s);
}


//Euclide algorithm (search greatest common denominator)
int algEuclide(int num1, int num2)
{
	int remainder = 1;
	while (num1 != 0)
	{
		remainder = num2 % num1;
		num2 = num1;
		num1 = remainder;
	}
	return num2;
}


//Reduce the fraction
void Fraction::reduce()
{
	int gcd = algEuclide(abs(_numerator), _denominator);
	_numerator /= gcd;
	_denominator /= gcd;
}


//Comparison overload '<'
bool operator<(int n, Fraction& f)
{
	if ((n * f._denominator) < f._numerator)
		return true;
	else
		return false;
}


//Comparison overload '>'
bool operator>(int n, Fraction& f)
{
	if ((n * f._denominator) > f._numerator)
		return true;
	else
		return false;
}


//Type conversion overload
Fraction::operator char*()
{
	static char s[32];
	sprintf(s, "%d/%d", _numerator, _denominator);
	return s;
}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Wrong number of arguments." << endl;
		return (-1);
	}

	Fraction frac(argv[2]);

	if (frac.getDenominator() == 0)
	{
		cout << "Incorrect input of fraction." << endl;
		return (-1);
	}

	frac.reduce();

	int num = atoi(argv[1]);
	if (num > frac)
		cout << num << " > " << (char*)frac << endl;
	else if (num < frac)
		cout << num << " < " << (char*)frac << endl;
	else
		cout << num << " = " << (char*)frac << endl;

	return 0;
}