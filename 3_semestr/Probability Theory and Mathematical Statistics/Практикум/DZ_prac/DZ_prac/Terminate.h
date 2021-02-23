#pragma once
#ifndef TERMANATEH
#define TERMANATEH


#include "State.h"
class TERMINATE : public State
{
public:
	TERMINATE(); //Конструктор класса
	void useTransact(Transact& transact, std::ofstream& file); //Вывод сообщения
};

#endif