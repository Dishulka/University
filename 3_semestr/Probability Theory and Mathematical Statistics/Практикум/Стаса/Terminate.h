#pragma once
#ifndef TERMANATEH
#define TERMANATEH


#include "State.h"
class Terminate : public State
{
private:

public:
	Terminate();
	void useTransact(Transact& transact, std::ofstream& file);
};

#endif // !TERMANATEH