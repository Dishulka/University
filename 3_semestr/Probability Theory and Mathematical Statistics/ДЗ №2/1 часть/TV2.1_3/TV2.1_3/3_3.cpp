#include <iostream>
#include <iomanip>
using namespace std;

double comb(int n, int k)
{
	if ((k == 0) || (k == n))
		return 1;
	if ((k == 1) || (k == n - 1))
		return n;

	int numStart;
	if (k > (n / 2))
		numStart = k + 1;
	else
		numStart = (n - k) + 1;

	int denom;
	if (k > (n / 2))
		denom = n - k;
	else
		denom = k;

	int amount;
	if (denom > (n - numStart))
		amount = n - numStart + 1;
	else
		amount = denom;

	double res = 1;
	int divider = 1, multiplier = numStart;
	for (int i = 1; i <= amount; ++i)
	{
		res *= multiplier;
		res /= divider;

		multiplier++;
		divider++;
	}

	return res;
}


double dispersion(int r, int N)
{
	double res1 = 0, res2 = 0;
	for (int k = r; k <= N; ++k)
	{
		double P = comb(k - 1, k - r) / comb(N, r);
		res1 += (double)(k * k) * P;
		res2 += (double)(k)*P;
	}

	res2 = pow(res2, 2);
	return (res1 - res2);
}

int main()
{
	int r = 6, g = 9, b = 8;
	int N = r + g + b;

	cout << "D = " << dispersion(r, N) << endl;

	return 0;
}