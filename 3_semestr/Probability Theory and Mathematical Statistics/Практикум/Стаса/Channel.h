#pragma once
#ifndef CHANNELH
#define CHANNELH


#include "State.h"
#include "Queue.h"

class Channel : public State
{
private:
	unsigned long long int _MIN;
	unsigned long long int _MAX;
	bool _isOccupied;
	Transact* _occupied;
	Queue _queue;
public:
	Channel(unsigned long long int min, unsigned long long int max);
	int getQueueSize();
	bool isOccupied();
	void useTransact(Transact& transact, std::ofstream& file);

};

#endif // !CHANNELH

