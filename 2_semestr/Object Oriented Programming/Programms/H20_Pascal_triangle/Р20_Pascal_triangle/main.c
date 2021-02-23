#include <stdio.h>
#include <stdlib.h>


//Calculate width of field for centering
int widthField(int n)
{
	int res = 1, max = -1;
	for (int i = 1; i <= n; i++)
	{
		res *= (n - i + 1);
		res /= i;
		if (max < res)
			max = res;
	}

	int countNum = 0;
	while (max != 0)
	{
		max /= 10;
		countNum++;
	}

	return countNum;
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Wrong number of arguments.\n");
		return 0;
	}


	int n = atoi(argv[1]);
	if (n <= 0)
	{
		printf("Wrong input format. Row count - whole number > 0.\n");
		return 0;
	}

	
	int width = widthField(n - 1);
	int indent = (n - 1) * width;
	for (int i = 0; i < n; i++)
	{
		int cnk = 1;
		printf("%*d", indent + width, cnk);
		for (int j = 1; j <= i; j++)
		{
			cnk *= (i - j + 1);
			cnk /= j;
			printf("%*d", width + width, cnk);
		}
		indent -= width;
		printf("\n");
	}
}