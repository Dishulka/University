#pragma once
#ifndef QUEUEH
#define QUEUEH

#include <list>
#include "Transact.h"
#include <iterator>
class QUEUE
{
private:
	std::list <Transact*> _transacts; //Список указателей на объекты Transact
public:
	QUEUE();							//Конструктор
	int getSize();						//Возвращает длину очереди
	void addTransact(Transact*);		//Добавляет в очередь указатель на новый объект 
	Transact* popTransact();			//Возвращает 1 из очереди указатель
	bool hasTransact(Transact& transact); //Проверяет наличие транзакта в очереди

};

#endif