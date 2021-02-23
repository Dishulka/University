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
	double p = (double)r / ((double)r + (double)g + (double)b);
	double q = 1 - p;

	double N1 = (long double)r + (long double)g + (long double)b;
	for (int k = 17; k <= n; k++)
	{
		double f = (double)(400 - 8 * k) / ((double)20 * sqrt((double)n * 0.24));
		cout << k << ": " << f << endl;
	}


	return 0;
}