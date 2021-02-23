#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>


class Point
{
private:
	int _x;
	int _y;
public:
	Point(int x, int y) : _x(x), _y(y) {};
	int getx() { return _x; };
	int gety() { return _y; };
	friend int differ(const void*, const void*);
	int differ(const Point*);
};


inline int Point::differ(const Point* p)
{
	return (p->_x - this->_x);
}


int differ(const void* a, const void* b)
{
	Point** p = (Point**)a;
	Point** q = (Point**)b;
	return (p[0]->_y - q[0]->_y);
}


int main(int argc, char* argv[]) 
{
	if (argc < 2)
	{
		return (-1);
	}
	Point** p;
	int x, y, i = 0, j, n = 0;
	p = new Point*[argc - 1];
	while (++i < argc)
	{
		x = 0;
		y = 0;
		sscanf(argv[i], "%d%*c%d", &x, &y);
		p[n++] = new Point(x, y);
	}
	qsort((void*)p, n, sizeof(Point*), differ);
	for (i = 0; i < n; i++)
	{
		printf("(%d;%d) > ", p[i]->getx(), p[i]->gety());
		for (j = 0; differ(&p[j], &p[i]) < 0; j++)
		{
			if (p[i]->differ(p[j]) < 0)
				printf("(%d;%d) ", p[j]->getx(), p[j]->gety());
		}
		printf("\n");
	}
	for (i = 0; i < n; i++)
	{
		delete p[i];
	}
	delete[]p;
	return 0;
}