#pragma once
#ifndef CHANNELH
#define CHANNELH


#include "State.h"
#include "Queue.h"

class OPERATOR : public State
{
private:
	int _min;				//Минимальное число для генератора
	int _max;				//Максимальное число для генератора
	bool _isBusy;			//Флаг, показывает занят или нет оператор
	Transact* _served;		//Указатель на транзакт, который обслуживается
	QUEUE _queue;			//Очередь к оператору
public:
	OPERATOR(int min, int max);	//Конструтор
	int getSize();				//Возвращаети длину очереди к оператору
	bool isBusy();				//Возвращает значение флага
	void useTransact(Transact& transact, std::ofstream& file); //Вывод сообщения
};

#endif 

