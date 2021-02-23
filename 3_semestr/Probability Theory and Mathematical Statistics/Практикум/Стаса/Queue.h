#pragma once
#ifndef QUEUEH
#define QUEUEH

#include <list>
#include "Transact.h"
#include <iterator>
class Queue
{
private:
	std::list <Transact*> _transacts;
	
public:
	Queue();
	int getSize();
	void addTransact(Transact*);
	Transact* ejectTransact();
	bool hasTransact(Transact& transact);

};

#endif // !QUEUEH