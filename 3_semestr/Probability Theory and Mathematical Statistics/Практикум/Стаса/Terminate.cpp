#include "Terminate.h"

Terminate::Terminate() : State()
{
}

void Terminate::useTransact(Transact& transact, std::ofstream& file)
{
	file << "At " << transact.getTimeNextEvent() << " transact with ID " << transact.getID() << " leave." << std::endl;
	delete &transact;
}
