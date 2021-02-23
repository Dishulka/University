#include <stdio.h>
#include <stdlib.h>


class Magic
{
private:
	unsigned** square;
	int _row;
	int _col;
	int _degree;
	void alg_Bashe();
public:
	Magic(int);
	~Magic();
	void Fill();
	void Print();
};


Magic::Magic(int n)
{
	_degree = n;
	square = new unsigned*[_degree];
	for (_row = 0; _row < _degree; ++_row)
		square[_row] = new unsigned[_degree];
	for (_row = 0; _row < _degree; ++_row)
		for (_col = 0; _col < _degree; ++_col)
			square[_row][_col] = 0;
}


Magic::~Magic()
{
	for (_row = 0; _row < _degree; ++_row)
		delete[] square[_row];
	delete[] square;
}


void Magic::Fill()
{
	for (int i = 0; i < _degree; ++i)
		for (int j = 0; j < _degree; ++j)
			square[i][j] = _degree * (_degree - i) - j;
	Print();
	alg_Bashe();
}


void Magic::Print()
{
	int num = _degree * _degree, len = 0;
	while (num != 0)
	{
		num /= 10;
		++len;
	}
	for (int i = 0; i < _degree; ++i)
	{
		for (int j = 0; j < _degree; ++j)
		{
			printf("%*d ", len, square[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void Magic::alg_Bashe()
{
	for (int i = 0; i < _degree; ++i)
	{
		for (int j = 0; j < _degree; ++j)
		{
			int shift_i = _degree / 2 - j, shift_j = _degree / 2 - i;
			if (i - shift_i < 0)
				square[i - shift_i + _degree][j + shift_j] = _degree * (_degree - i) - j;
			else if (i - shift_i >= _degree)
				square[i - shift_i - _degree][j + shift_j] = _degree * (_degree - i) - j;
			else if (j + shift_j >= _degree)
				square[i - shift_i][j + shift_j - _degree] = _degree * (_degree - i) - j;
			else if (j + shift_j < 0)
				square[i - shift_i][j + shift_j + _degree] = _degree * (_degree - i) - j;
			else 
				square[i - shift_i][j + shift_j] = _degree * (_degree - i) - j;
		}
	}
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Don't enter magic degree\n");
		return 0;
	}
	int n = atoi(argv[1]);
	if (n % 2 == 0)
	{
		printf("Magic degree should be odd number\n");
		return 0;
	}
	Magic mag_square(n);
	mag_square.Fill();
	mag_square.Print();
	return 0;
}