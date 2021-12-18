#include <iostream>
#include <vector>
using namespace std;


void PrintSplit(vector<int> vec) {
	for (int i = 0; i < vec.size() - 2; i += 2) {
		cout << vec[i] << "*" << vec[i + 1] << " + ";
	}
	cout << vec[vec.size() - 2] << "*" << vec.back();
	cout << endl;
}


vector<int> InsertNewSplit(vector<int> vec, int k, int p) {
	for (int i = vec.size() - 1; i > 0; i -= 2) {
		if (vec[i] > p) {
			vec.insert(vec.begin() + i + 1, p);
			vec.insert(vec.begin() + i + 1, k);
			return vec;
		}
		else if (vec[i] == p) {
			vec[i - 1] += k;
			return vec;
		}
	}
	vec.insert(vec.begin(), p);
	vec.insert(vec.begin(), k);
	return vec;
}


int SumCurrSplit(vector<int> vec) {
	int sum = 0;
	for (int i = 0; i < vec.size(); i += 2) {
		sum += vec[i] * vec[i + 1];
	}
	return sum;
}


vector<int> CompleteOnes(vector<int> vec, int n) {
	int sum = SumCurrSplit(vec);
	if (sum != n) {
		if (vec.back() == 1) {
			vec[vec.size() - 2] += n - sum;
		}
		else {
			vec.insert(vec.end(), n - sum);
			vec.insert(vec.end(), 1);
		}
	}

	return vec;
}


vector<int> GenerateNextSplit(vector<int> currSplit, int n) {
	int sizeCurrSplit = currSplit.size();
	if (currSplit[sizeCurrSplit - 2] > 1) {
		currSplit[sizeCurrSplit - 2] -= 2;
		currSplit = InsertNewSplit(currSplit, 1, currSplit.back() + 1);
		sizeCurrSplit = currSplit.size();
		if (currSplit[sizeCurrSplit - 2] == 0) {
			currSplit.erase(currSplit.end() - 2, currSplit.end());
		}
		currSplit = CompleteOnes(currSplit, n);
	}
	else {
		currSplit.erase(currSplit.end() - 2, currSplit.end());
		int deletedValue = currSplit.back();
		currSplit.erase(currSplit.end() - 2, currSplit.end());
		currSplit = InsertNewSplit(currSplit, 1, deletedValue + 1);
		currSplit = CompleteOnes(currSplit, n);
	}

	return currSplit;
}


int main(int argc, char** argv)
{
	if (argc < 4) {
		std::cout << "Enter n, L, U" << endl;
		exit(-1);
	}

	int n = atoi(argv[1]);
	if (n <= 0) {
		std::cout << "N must be more than 0" << endl;
		exit(-2);
	}

	int L = atoi(argv[2]);
	if (L <= 0) {
		std::cout << "L must be more than 0" << endl;
		exit(-3);
	}

	int U = atoi(argv[3]);
	if (U <= 0) {
		std::cout << "U must be more than 0" << endl;
		exit(-4);
	}

	if (U < L) {
		std::cout << "U must be more or equal L" << endl;
		exit(-4);
	}

	vector<int> startSplit = { n, 1 };
	vector<int> finishSplit = { 1, n };
	cout << "n=" << n << endl;
	cout << "[L,U]=[" << L << "," << U << "]" << endl;
	cout << endl;

	int total = 0;
	while (startSplit != finishSplit) {
		if (startSplit[1] >= L && startSplit[1] <= U) {
			cout << ++total << ": ";
			PrintSplit(startSplit);
		}
		startSplit = GenerateNextSplit(startSplit, n);
	}

	if (startSplit[1] >= L && startSplit[1] <= U) {
		cout << ++total << ": ";
		PrintSplit(startSplit);
	}

	cout << "Total: " << total << endl;

	return 0;
}