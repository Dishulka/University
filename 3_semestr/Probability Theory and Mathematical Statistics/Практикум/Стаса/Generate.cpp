#include "Generate.h"

Generate::Generate(unsigned long long int min, unsigned long long int max) :State()
{
	_time = 0;
	_MIN = min;
	_MAX = max;
}

double Generate::getTime()
{
	_time += (double)(_MIN + ((unsigned long long int)rand() % ((unsigned long long int)_MAX - 1)) + (double)rand() / RAND_MAX);
	return _time;
}

void Generate::useTransact(Transact& transact, std::ofstream& file)
{
	transact.setState(_nextState);
	file << "At " << transact.getTimeNextEvent() << " transact with ID " << transact.getID() << " generated." << std::endl;
}
