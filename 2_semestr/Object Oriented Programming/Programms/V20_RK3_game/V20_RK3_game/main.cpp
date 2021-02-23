#include <iostream>
#include <stdlib.h>
using namespace std;


class Heap
{
private:
	int _size;							//size of heap
public:
	Heap(int size) : _size(size) {};
	int getSize(int n = 0) 
	{
		_size -= n;
		return _size;
	};
};


class Game
{
protected:
	Heap* _heap;				//Pointer at heap
	const int _limit;			//Limit value (how much we can take at time)
	const char* _name;			//Name of player
	int _lastMove;				//Last value we took from heap
public:
	Game(Heap& h, int lim, int move = 0) : _limit(lim), _lastMove(move)
	{
		_heap = &h;
	};
	int status();									//Query before move players
	virtual int move() = 0;							//Virtual function of move players
	void changeMove(int n) { _lastMove = n; };		//Change last move
	~Game() {};
};


//Query before move players
int Game::status()
{
	cout << "Heap = " << _heap->getSize() << endl;
	cout << _name << ": ";
	return _heap->getSize();
}


class Player : public Game
{
public:
	Player(Heap& h, int lim, const char* name) : Game(h, lim) { _name = name; };
	virtual int move();
};

 
class Computer : public Game
{
public:
	Computer(Heap& h, int lim, const char* name) : Game(h, lim) { _name = name; };
	virtual int move();
};


int Player::move()
{
	int num;
	cin >> num;
	if ((num < 1) || (num > _limit) || (num > _heap->getSize()))
		num = _limit;
	if (num > _heap->getSize())
		num = _heap->getSize();
	_lastMove = num;
	return _heap->getSize(num);
}


int Computer::move()
{
	int sizeHeap = _heap->getSize();
	if (sizeHeap < _limit)
	{
		_lastMove = sizeHeap;
		cout << sizeHeap << endl;
		return _heap->getSize(sizeHeap);
	}
	else
	{
		int remainder = sizeHeap % (_limit + 1);
		if (remainder != 0)
		{
			_lastMove = remainder;
			cout << remainder << endl;
			return _heap->getSize(remainder);
		}
		else
		{
			cout << _lastMove << endl;
			return _heap->getSize(_lastMove);
		}
	}
}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Wrong number of arguments." << endl;
		return (-1);
	}

	Heap heap(atoi(argv[1]));
	if (heap.getSize() <= 0)
	{
		cout << "Wrong heap input." << endl;
		return (-1);
	}

	int limMove = atoi(argv[2]);
	if (limMove <= 0)
	{
		cout << "Wrong limit value of move input." << endl;
		return (-1);
	}

	Game* player[] = { new Player(heap, limMove, "Player"), new Computer(heap, limMove, "Computer") };

	int i = 0, sizeHeap = heap.getSize(), move = sizeHeap;
	while (player[i]->status() != 0)
	{
		sizeHeap = player[i]->move();
		move -= sizeHeap;

		if (i == 0)
			player[1]->changeMove(move);
		else
			player[0]->changeMove(move);

		move = sizeHeap;

		i++;
		if (i > 1)
			i = 0;
	}
	cout << "Loser" << endl;
	delete player[0];
	delete player[1];
	return 0;
}