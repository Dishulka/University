#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong number of arguments." << endl;
		return (-1);
	}

	ifstream f_in;
	f_in.open(argv[1]);
	if (!f_in.is_open())
	{
		cout << "File could not open." << endl;
		return (-1);
	}

	ofstream f_out;
	f_out.open("new.txt");

	bool prevLine = false;
	while (!f_in.eof())
	{
		string buffer;
		getline(f_in, buffer);
		int i = 0;
		bool lineBlank = true;
		while ((lineBlank) && (buffer[i] != '\0'))
		{
			if ((buffer[i] != ' ') && (buffer[i] != '	'))
			{
				lineBlank = false;
			}
			++i;
		}
		if (!lineBlank)
		{
			if (f_in.eof())
				f_out << buffer;
			else
				f_out << buffer << endl;
			prevLine = false;
		}
		else if (!prevLine)
		{
			if (f_in.eof())
				f_out << buffer;
			else
				f_out << buffer << endl;
			prevLine = true;
		}
	}

	f_in.close();
	f_out.close();

	f_out.open(argv[1]);
	f_in.open("new.txt");
	while (!f_in.eof())
	{
		string buffer;
		getline(f_in, buffer);
		if (f_in.eof())
		{
			f_out << buffer;
			cout << buffer;
		}
		else
		{
			f_out << buffer << endl;
			cout << buffer << endl;
		}
	}

	f_in.close();
	f_out.close();
	remove("new.txt");

	return 0;
}