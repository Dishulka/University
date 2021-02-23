#include "Transact.h"

int Transact::_currID = 0;

Transact::Transact()
{
	_ID = _currID;
	_currID++;
	_state = 0;
	_time = 0;
}

int Transact::getID()
{
	return _ID;
}

double Transact::getTime()
{
	return _time;
}

int Transact::getState()
{
	return _state;
}

void Transact::setTime(double time)
{
	_time = time;
}

void Transact::setState(int state)
{
	_state = state;
}

