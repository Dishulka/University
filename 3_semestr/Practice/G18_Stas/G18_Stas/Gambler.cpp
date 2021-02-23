#include "Gambler.h"

const char* Gambler::getName()
{
	return _name;
}

Gambler::Gambler(Figure& f)
{
	_figure = &f;
}

void Gambler::query()
{
	std::cout << _name <<": "<< (*_figure)<<"-"<<_figure->isA();
	return;
}


Man::Man(Figure& f, const char* n) :Gambler(f)
{
	_name = n;
}

bool Man::move()
{
	char s[3];
	std::cin.unsetf(std::ios::skipws);
	std::cin >> s[0] >> s[1];
	s[2] = '\0';
	std::cin.ignore(64, '\n');
	if (Figure::deskOut(s) || (_figure->attack(s) == 0) || (*_figure) == s)
		return false;
	(*_figure) = s;
	return true;
}


Pen::Pen(Figure& f, const char* n) :Gambler(f)
{
	_name = n;
}

bool Pen::move()
{
	static char s[3];
	s[0] = _figure->getAlp();
	s[1] = _figure->getNum();
	s[2] = '\0';

	s[0] = (s[0] - 'a') % 2 != 0 ? s[0] : (s[0] + 1);
	s[1] = (s[1] - '1') % 2 != 0 ? s[1] : (s[1] + 1);

	(*_figure) = s;
	std::cout << s;
	std::cin.ignore(64, '\n');
	return true;
}