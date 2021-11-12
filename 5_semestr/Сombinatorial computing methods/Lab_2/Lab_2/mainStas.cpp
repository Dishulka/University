#include <iostream>
#include <vector>
#define LEN 5


int factorial(int x)
{
	return (x < 2) ? 1 : x * factorial(x - 1);
}


void print_next_transposition(int n)
{
	std::vector<int> max_transp;	//5 4 3 2 1
	int ans[LEN];	//result vector
	int v[LEN];	//vector of inversions
	for (int i = LEN; i >= 1; i--)
	{
		max_transp.push_back(i);
	}
	v[0] = 0;
	for (int i = LEN - 1; i > 0; i--)	//finding vector of inversions
	{
		v[i] = n / factorial(i);
		n = n - factorial(i) * v[i];
	}
	for (int i = LEN - 1; i >= 0; i--)
	{
		int j = v[i];
		ans[i] = max_transp[j];
		max_transp.erase(max_transp.begin() + j);
	}
	for (int i = 0; i < LEN; i++)
	{
		std::cout << ans[i] << ' ';
	}
	std::cout << '\n';
}

int main()
{
	int numb = 1;
	for (int n = factorial(LEN) - 1; n >= 0; n--)
	{
		std::cout << numb << ": ";
		print_next_transposition(n);
	}
}