#include "Terminate.h"
using namespace std;

TERMINATE::TERMINATE():State()
{
}

void TERMINATE::useTransact(Transact& transact, std::ofstream& file)
{
	file << "В момент времени " << transact.getTime() << " тразакт с индентификатором " << transact.getID() << " вышел из модели." << endl;
	delete &transact;
}
