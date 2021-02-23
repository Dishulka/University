#include <stdio.h>
#include <math.h>


class Point
{
private:
	int _x;
	int _y;
public:
	int getx()
	{
		return _x;
	}
	int gety()
	{
		return _y;
	}
	Point(int x, int y) : _x(x), _y(y) {};
};


double distance(Point* a, Point* b)
{
	double ans = (double)((a->getx() - b->getx()) * (a->getx() - b->getx())) + (double)((a->gety() - b->gety()) * (a->gety() - b->gety()));
	return sqrt(ans);
}


void calc(Point** a)
{
	double max_d = -1;
	int ind1, ind2;
	for (int i = 0; a[i] != NULL; ++i)
		for (int j = i + 1; a[j] != NULL; ++j)
		{
			int sum1 = a[i]->getx() + a[i]->gety(), sum2 = a[j]->getx() + a[j]->gety();
			if (((sum1 > 0) && (sum2 < 0)) || ((sum1 < 0) && (sum2 > 0)))
			{
				double d = distance(a[i], a[j]);
				if (max_d < d)
				{
					max_d = d;
					ind1 = i;
					ind2 = j;
				}
			}
		}
	if (max_d == -1)
		printf("No such points.\n");
	else
		printf("Max dist between 2 points: (%d;%d) and (%d;%d) = %lf\n", a[ind1]->getx(), a[ind1]->gety(), a[ind2]->getx(), a[ind2]->gety(), max_d);
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("No points.\n");
		return(-1);
	}
	Point** p;
	p = new Point * [argc];
	int i = 1, j = 0, x, y;
	while (i < argc)
	{
		sscanf(argv[i], "(%d%*c%d)", &x, &y);
		p[j] = new Point(x, y);
		++i;
		++j;
	}
	p[j] = NULL;

	calc(p);
	
	for (j = 0; p[j] != NULL; ++j)
		delete p[j];
	delete[]p;
	return 0;
}