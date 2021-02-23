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


double SumOfMult(double tService, double tApplication, double tWaiting, double n, int i)
{
	double result = 0;
	for (int j = 1; j <= i; j++)
	{
		double temp = 1;
		for (int k = 1; k <= j; k++)
		{
			temp *= (1 / tApplication) / (n / tService + k / tWaiting);
		}
		result += temp;
	}
	return  result;

}


double calcMathExpectingOP(double tService, double tApplication, double tWaiting, double n, int j, double Pn, double P0)
{
	double result = 0;
	for (int i = 0; i <= n; i++)
	{
		result += i * powl(tService / tApplication, i) / factorial(i);
	}
	result *= P0;
	result += n * Pn * SumOfMult(tService, tApplication, tWaiting, n, j);
	return result;
}


double calcP0(double tService, double tApplication, double tWaiting, double n, int j)
{
	double result = 0;
	for (int i = 0; i <= n; i++)
	{
		result += pow(tService / tApplication, i) / factorial(i);
	}
	result += powl(tService / tApplication, n) * SumOfMult(tService, tApplication, tWaiting, n, j) / factorial(n);
	return 1 / result;
}


double SumOfMultCommon(double tService, double tApplication, double tWaiting, double n, int i)
{
	double result = 0;
	for (int j = 1; j <= i; j++)
	{
		long double temp = 1;
		for (int k = 1; k <= j; k++)
		{
			temp *= (1 / tApplication) / (n / tService + k / tWaiting);
		}
		result += j * temp;
	}
	return  result;
}


int main()
{
	int tService = 11, tApplication = 20, tWaiting = 23;
	int operators = 4;
	double P0, temp, Pn, MathExpectQ;
	double r = (double)tService / (double)tApplication;

	for (int n = 1; n <= operators; n++)
	{
		P0 = 0;
		MathExpectQ = 0;

		temp = calcP0(tService, tApplication, tWaiting, n, 1);
		P0 = calcP0(tService, tApplication, tWaiting, n, 2);
		int k = 2;
		while (abs(temp - P0) > 0e-7)
		{
			k++;
			temp = P0;
			P0 = calcP0(tService, tApplication, tWaiting, n, k);
		}

		Pn = P0 * pow(r, n) / factorial(n);

		temp = Pn * SumOfMultCommon(tService, tApplication, tWaiting, n, 1);
		MathExpectQ = Pn * SumOfMultCommon(tService, tApplication, tWaiting, n, 2);
		k = 2;
		while (abs(temp - MathExpectQ) > 0e-7)
		{
			k++;
			temp = MathExpectQ;
			MathExpectQ = Pn * SumOfMultCommon(tService, tApplication, tWaiting, n, k);
		}

		cout << n << ": " << MathExpectQ << endl;
	}

	return 0;
}