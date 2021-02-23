#pragma once
#ifndef TRANSACTH

class Transact 
{
private:
	static unsigned long long int _currID;
	unsigned long long _ID;
	double _timeNextEvent;
	unsigned int _state;
public:
	Transact();
	unsigned long long int getID();
	double getTimeNextEvent();
	unsigned int getState();
	void setTimeNextEvent(double input);
	void setState(unsigned int input);
};

#define TRANSACTH
#endif // !TRANSACTH



