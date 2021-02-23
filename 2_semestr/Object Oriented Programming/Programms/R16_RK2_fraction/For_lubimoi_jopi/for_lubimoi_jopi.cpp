#pragma warning(disable : 4996)

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
using namespace std;


class Fraction
{
private:
	int nom;
	int den;
public:
	Fraction(int n = 0, int m = 1) : nom(n), den(m) {};
	Fraction(char* s);
	void reduce();
	operator char* ();
	int getDen() { return den; };
	Fraction& operator=(Fraction& f);
	friend Fraction& operator*(Fraction& f, int n);
};


Fraction::Fraction(char* s)
{
	char* p = strchr(s, '/');
	den = 1;
	if (p != NULL)
	{
		*p++ = '\0';
		den = atoi(p);
	}
	nom = atoi(s);
}


int euclide(int n, int m)
{
	int r = 1;
	while (n != 0)
	{
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}


void Fraction::reduce()
{
	int gcd = euclide(abs(nom), den);
	nom /= gcd;
	den /= gcd;
}


Fraction::operator char* ()
{
	static char s[32];
	sprintf(s, "%d/%d", nom, den);
	return s;
}

Fraction& Fraction::operator=(Fraction& f)
{
	nom = f.nom;
	den = f.den;
	return *this;
}


Fraction& operator*(Fraction& f, int n)
{
	f.nom *= n;
	return f;
}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Wrong number of arguments." << endl;
		return (-1);
	}

	Fraction f(argv[2]);
	f.reduce();
	if (f.getDen() == 0)
	{
		cout << "Denominator should not be 0." << endl;
		return (-1);
	}

	int num = atoi(argv[1]);
	f = (f * num);
	f.reduce();

	cout << (char*)f << endl;

	return 0;
}