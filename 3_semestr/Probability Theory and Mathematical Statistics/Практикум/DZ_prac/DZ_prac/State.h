#pragma once
#ifndef STATEH
#define STATEH

#include "Transact.h"
#include <fstream>
class State
{
protected:
	static int _currID;			//Идентификатор объекта класса
	int _ID;					//Идентификатор экземпляра класса
	int _state;					//Номер следющего состояния транзакта
public:
	State();								//Конструтор класса
	int getID();							//Возвращает идентификатор 
	void setState(int state);				//Возвращает номер следующего состояния
	virtual void useTransact(Transact& transact, std::ofstream& file) = 0;	//Виртуальный метод
};

#endif