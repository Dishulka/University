#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	cout << endl;

	int r = 8, g = 7, b = 5;
	double p = (double)r / (double)(r + g + b);
	double q = 1 - p;

	int addition = n / 7, summ = 0;
	for (int i = 0; i < 7; ++i)
	{
		double x = ((double)summ - (double)n * p) / sqrt((double)n * p * q);
		cout << "F(" << setprecision(4) << x << ") = ";

		double tabularValue;
		cin >> tabularValue;

		double P;
		P = tabularValue / sqrt((double)n * p * q);
		cout << "P(" << summ << ") = " << setprecision(4) << P << endl;
		cout << endl;

		summ += addition;
	}

	return 0;
}