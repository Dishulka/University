#include <iostream>
#include <cmath>
using namespace std;


class Triangle;
class Dot
{
private:
	double _x;
	double _y;
public:
	Dot(double x = 0.0, double y = 0.0) : _x(x), _y(y) {};
	friend class Triangle;
};


class Triangle
{
private:
	Dot A;
	Dot B;
	Dot C;
public:
	Triangle(Dot d1, Dot d2, Dot d3) : A(d1), B(d2), C(d3) {};
	Triangle() {};
	double angleABC();
	double angleBCA();
	double angleCAB();
	bool exist_triangle();
};


bool Triangle::exist_triangle()
{
	if ((((A._x - C._x) * (B._y - C._y) - (B._x - C._x) * (A._y - C._y)) / 2) == 0)
		return false;
	else
		return true;
}


double Triangle::angleABC()
{
	double x1 = (B._x - A._x), x2 = (B._x - C._x), y1 = (B._y - A._y), y2 = (B._y - C._y);
	double sqrt1 = sqrt(x1 * x1 + y1 * y1), sqrt2 = sqrt(x2 * x2 + y2 * y2);
	return acos((x1*x2 + y1 * y2) / sqrt1 / sqrt2) * 180.0 / 3.14159265;
}


double Triangle::angleBCA()
{
	double x1 = (C._x - B._x), x2 = (C._x - A._x), y1 = (C._y - B._y), y2 = (C._y - A._y);
	double sqrt1 = sqrt(x1 * x1 + y1 * y1), sqrt2 = sqrt(x2 * x2 + y2 * y2);
	return acos((x1*x2 + y1 * y2) / sqrt1 / sqrt2) * 180.0 / 3.14159265;
}


double Triangle::angleCAB()
{
	double x1 = (A._x - B._x), x2 = (A._x - C._x), y1 = (A._y - B._y), y2 = (A._y - C._y);
	double sqrt1 = sqrt(x1 * x1 + y1 * y1), sqrt2 = sqrt(x2 * x2 + y2 * y2);
	return acos((x1*x2 + y1 * y2) / sqrt1 / sqrt2) * 180.0 / 3.14159265;
}


bool input_coord(Triangle* Tr)
{
	double x, y;
	Dot point[3];
	for (int i = 0; i < 3; ++i)
	{
		cout << "Input 2 coordinates of dot " << (char)(65 + i) << " in format: \"x y\" " << endl;
		if (cin >> x >> y)
		{
			Dot temp(x, y);
			point[i] = temp;
		}
		else
			return false;
	}
	Triangle Tr_temp(point[0], point[1], point[2]);
	*Tr = Tr_temp;
	return true;
}


int main()
{
	Triangle ABC;
	while (input_coord(&ABC))
	{
		if (!(ABC.exist_triangle()))
		{
			cout << "Dots lie on 1 line or dots matches. Triangle don't exist." << endl;
			return 0;
		}
		cout << "Angle ABC = " << ABC.angleABC() << " degree" << endl;
		cout << "Angle BCA = " << ABC.angleBCA() << " degree" << endl;
		cout << "Angle CAB = " << ABC.angleCAB() << " degree" << endl;
		return 0;
	}
	cout << "Wrong input of coordinates" << endl;
	return 0;
}