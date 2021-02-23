#pragma once
#ifndef TRANSACTH

class Transact 
{
private:
	static int _currID;				//Идентификатор объекта класса
	int _ID;						//Идентификатор экземпляра класса
	double _time;					//Время следующей обработки
	int _state;						//Номер текщего состояния
public:
	Transact();							//Конструтор класса
	int getID();						//Возвращает идентификатор		
	double getTime();					//Возвращает время 
	int getState();						//Возвращает текщее состяние
	void setTime(double time);			//Устанавливает время
	void setState(int state);			//Устанавливает номер текщего состояния
};

#define TRANSACTH
#endif


