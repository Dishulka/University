#pragma once
#ifndef GENERATEH
#define GENERATEH

#include "State.h"
#include <cstdlib>

class Generate : public State
{
private:
	double _time;
	unsigned long long int _MAX;
	unsigned long long int _MIN;
public:
	Generate(unsigned long long int, unsigned long long int);
	double getTime();
	void useTransact(Transact& transact, std::ofstream& file);
};


#endif // !GENERATEH



