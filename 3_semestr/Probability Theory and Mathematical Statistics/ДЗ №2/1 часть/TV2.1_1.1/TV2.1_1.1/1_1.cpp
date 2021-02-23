#include <iostream>
#include <iomanip> 
#include <math.h>
using namespace std;

int factorial(int a)
{
	int res = 1;
	for (int i = a; i > 1; --i)
	{
		res *= i;
	}
	return res;
}

double comb(int n, int k)
{
	return (double)factorial(n) / ((double)factorial(k) * (double)factorial(n - k));
}

int main()
{
	int n;
	cin >> n;

	int r1 = 8, g1 = 7, b1 = 5;
	double p = (double)r1 / (double)(r1 + g1 + b1);

	for (int i = 0; i <= n; ++i)
	{
		double P = comb(n, i) * pow(p, i) * pow((1 - p), (n - i));
		cout << "P("  <<  i << ")= " << setprecision(6) <<  P << endl;
	}
	return 0;
}

