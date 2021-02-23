#include "Transact.h"
unsigned long long int Transact::_currID = 0;

Transact::Transact()
{
	_ID = _currID;
	_currID++;
	_state=0;
	_timeNextEvent = 0;
}

unsigned long long int Transact::getID()
{
	return _ID;
}

double Transact::getTimeNextEvent()
{
	return _timeNextEvent;
}

unsigned int Transact::getState()
{
	return _state;
}

void Transact::setTimeNextEvent(double input)
{
	_timeNextEvent = input;
}

void Transact::setState(unsigned int input)
{
	_state = input;
}

