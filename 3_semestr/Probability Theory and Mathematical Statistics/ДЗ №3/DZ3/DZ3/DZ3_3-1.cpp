#include <iostream>
#include <iomanip>
using namespace std;


int factorial(int n)
{
	int res = 1;
	for (int i = 1; i <= n; ++i)
	{
		res *= i;
	}
	return res;
}


int main()
{
	int tService = 11, tApplication = 20;
	int operators = 4;
	double P0, Pn, MathExpectOP;
	double r = (double)tService / (double)tApplication;

	for (int n = 1; n <= operators; n++)
	{
		P0 = 0;
		MathExpectOP = 0;
	
		for (int i = 0; i <= n; i++)
		{
			P0 += pow(r, i) / factorial(i);
		}
		P0 += pow(r, (double)(n + 1)) / (factorial(n) * (n - r));
		P0 = 1 / P0;
	
		Pn = P0;
		for (int i = 1; i <= n; ++i) {
			Pn *= r;
			Pn /= i;
		}

		for (int i = 1; i <= n; ++i) {
			MathExpectOP += P0 * pow(r, i) / factorial(i);
		}
		MathExpectOP += n * Pn * (r / n) / (1 - (r / n));

		cout << n << ": " << MathExpectOP << endl;
	}
}