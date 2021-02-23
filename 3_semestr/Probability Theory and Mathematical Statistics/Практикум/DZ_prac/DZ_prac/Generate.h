#pragma once
#ifndef GENERATEH
#define GENERATEH

#include "State.h"
#include <cstdlib>

class GENERATE : public State
{
private:
	double _time;					//Время появления события
	int _max;						//Максимальное число для генератора
	int _min;						//Минимальное число для генератора
public:
	GENERATE(int min, int max);			//Констрктор класса
	double getTime();					//Возвращает время
	void useTransact(Transact& transact, std::ofstream& file); //Вывод сообщения
};


#endif 



