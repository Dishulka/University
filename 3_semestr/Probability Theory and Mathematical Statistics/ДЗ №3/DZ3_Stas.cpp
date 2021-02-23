#include <iostream>
#include <math.h>
#include <iomanip> 
#define EPS 0e-7
using namespace std;

long double fact(int);

long double SumOfMult(long double maintenanceTime, long double appearanceTime, long double waitingTime, long double channels, int i)
{
	long double result = 0;
	for (int j = 1; j <= i; j++)
	{
		long double temp = 1;
		for (int k = 1; k <= j; k++)
		{
			temp *= (1 / appearanceTime) / (channels / maintenanceTime + k / waitingTime);
		}
		result += temp;
	}
	return  result;

}
long double SumOfMultComlex(long double maintenanceTime, long double appearanceTime, long double waitingTime, long double channels, int i)
{
	long double result = 0;
	for (int j = 1; j <= i; j++)
	{
		long double temp = 1;
		for (int k = 1; k <= j; k++)
		{
			temp *= (1 / appearanceTime) / (channels / maintenanceTime + k / waitingTime);
		}
		result += j*temp;
	}
	return  result;

}
long double Punkt4P_0(long double maintenanceTime, long double appearanceTime, long double waitingTime, long double channels, int j)
{
	long double result = 0;
	for (int i = 0; i <= channels; i++)
	{
		result += powl(maintenanceTime / appearanceTime, i) / fact(i);
	}
	result += powl(maintenanceTime / appearanceTime, channels) * SumOfMult(maintenanceTime, appearanceTime, waitingTime, channels, j) / fact(channels);
	return 1 / result;

}
long double Punkt4MathExpectingChannels(long double maintenanceTime, long double appearanceTime, long double waitingTime, long double channels, int j, long double P_n, long double P_0)
{
	long double result = 0;
	for (int i = 0; i <= channels; i++)
	{
		result += i * powl(maintenanceTime / appearanceTime, i) / fact(i);
	}
	result *= P_0;
	result += channels * P_n * SumOfMult(maintenanceTime, appearanceTime, waitingTime, channels, j);
	return result;

}
long double Punkt4P_queue(long double maintenanceTime, long double appearanceTime, long double waitingTime, long double channels, int j, long double P_n, long double P_0)
{
	return P_n*SumOfMult(maintenanceTime, appearanceTime, waitingTime, channels, j);

}
long double Punkt4MathExpectingQueues(long double maintenanceTime, long double appearanceTime, long double waitingTime, long double channels, int j, long double P_n, long double P_0)
{
	return P_n * SumOfMultComlex(maintenanceTime, appearanceTime, waitingTime, channels, j);

}
long double fact(int n)
{
	long double r = 1;
	for (int i = 2; i <= n; ++i)
		r *= i;
	return r;
}
void Punkt1(long double maintenanceTime, long double appearanceTime)
{
	int channels = 1; // Кол-во каналов
	long double P_denial; // Вероятность отказов
	long double MathExpecting; // Математическое ожидание числа занятых операторов
	long double load_Factor; // Коэффициент загрузки операторов
	long double P_0;
	long double ro = maintenanceTime / appearanceTime; // Коэффициент загрузки СМО
	cout << "Канал\t\t";
	cout << "Отказ\t\t";
	cout << "Матож\t\t";
	cout << "Коэф\n";
	bool flag = true;
	do
	{

#pragma region P_0
		P_0 = 0;
		MathExpecting = 0;
		for (int i = 0; i <= channels; i++)
		{
			P_0 += powl(ro, i) / fact(i);
		}
		P_0 = 1 / P_0;
#pragma endregion

#pragma region Вероятность отказа
		P_denial = P_0 * powl(ro, (long double)channels) / fact(channels);
#pragma endregion

#pragma region Мат ожидание
		for (int i = 0; i <= channels; i++)
		{
			MathExpecting += i * P_0 * powl(ro, i) / fact(i);
		}
#pragma endregion

#pragma region Коэф. загрузки операторов
		load_Factor = MathExpecting / channels;
#pragma endregion

#pragma region Вывод
		cout << setprecision(5) << channels << "\t\t";
		cout << setprecision(5) << P_denial << "\t\t";
		cout << setprecision(5) << MathExpecting << "\t\t";
		cout << setprecision(5) << load_Factor << "\n";
#pragma endregion
		if (P_denial <= 0.01)
			flag = false;
		channels++;
	} while (flag);
}
void Punkt2(long double maintenanceTime, long double appearanceTime, long double maxChannels)
{
	long double P_0 = 0.0;
	long double P_denial;
	long double MathExpectingChannels; // Мат ожидание Каналов
	long double MathExpectingQueues; // Мат ожидание очереди
	long double P_queue; // Вероятность образования очереди
	long double loadFactorChannels; // Коэф. загрузки операторов
	long double loadFactorQueues; // Коэф. загрузки очереди

	long double ro = maintenanceTime / appearanceTime; // Коэффициент загрузки СМО
#pragma region Вывод для таблички
	cout << "Операт\t";
	cout << "Очередь\t";
	cout << "Отказ\t";
	cout << "МатОжОп\t";
	cout << "КоэфОп\t";
	cout << "ВерОч\t";
	cout << "МатОжОч\t";
	cout << "КоэфОч\n";
#pragma endregion
	for (int channels = 1; channels <= maxChannels; channels++)
	{

		int queue = 1;
		bool flag = true;
		do
		{
#pragma region Инициализация
			P_0 = 0;
			P_denial = 0;
			MathExpectingChannels = 0;
			MathExpectingQueues = 0;
			P_queue = 0;
			loadFactorChannels = 0;
			loadFactorQueues = 0;
#pragma endregion

#pragma region P_0
			for (int i = 0; i <= channels; i++)
			{
				P_0 += powl(ro, i) / fact(i);
			}
			P_0 += powl(ro, (long double)channels + 1) * (1 - powl(ro/ channels, queue) ) / (fact(channels) * (channels - ro));
			P_0 = 1 / P_0;
#pragma endregion

#pragma region Вероятность отказов
			P_denial = P_0 * powl(ro, (long double)queue + (long double)channels) / (powl(channels, queue) * fact(channels));
			if (P_denial <= 0.01 && queue >= 3)
				flag = false;
#pragma endregion

#pragma region Математическое ожидание числа занятых операторов
			for (int i = 0; i <= channels; i++)
			{
				MathExpectingChannels += i * P_0 * powl(ro, i) / fact(i);
			}
			for (int i = 1; i <= queue; i++)
			{
				MathExpectingChannels += channels * P_0 * pow(ro, channels + i) / (pow(channels, i) * fact(channels));
			}
#pragma endregion
			
#pragma region Коэффициент загрузки операторов
			loadFactorChannels = MathExpectingChannels / channels;
#pragma endregion

#pragma region Вероятность существования очереди
			P_queue = P_0 * (powl(ro, channels) * (1 - powl(ro / channels, queue))) / (fact(channels) * (1 - ro / channels));
#pragma endregion

#pragma region Математическое ожидания длины очереди
			for (int i = 1; i <= queue; i++)
			{
				MathExpectingQueues += i * P_0 * pow(ro, channels + i) / (pow(channels, i) * fact(channels));
			}
#pragma endregion

#pragma region Коэффициент занятости мест в очереди
			loadFactorQueues = MathExpectingQueues / queue;
#pragma endregion

#pragma region Вывод
			cout << setprecision(7) << channels << "\t";
			cout << setprecision(7) << queue << "\t";
			cout << setprecision(7) << P_denial << "\t";
			cout << setprecision(7) << MathExpectingChannels << "\t";
			cout << setprecision(7) << loadFactorChannels << "\t";
			cout << setprecision(7) << P_queue << "\t";
			cout << setprecision(7) << MathExpectingQueues << "\t";
			cout << setprecision(7) << loadFactorQueues << "\n";
#pragma endregion

			queue++;
		} while (flag);
	}
}
void Punkt3(long double maintenanceTime, long double appearanceTime, long double maxChannels)
{
	long double P_0 = 0.0;
	long double P_n = 0.0;
	long double P_queue = 0.0;
	long double MathExpectingChannels; // Мат ожидание Каналов
	long double MathExpectingQueues; // Мат ожидание очереди
	long double loadFactorChannels; // Коэф. загрузки операторов
	long double temp;
	long double ro = maintenanceTime / appearanceTime; // Коэффициент загрузки СМО
	cout << "Опер\t";
	cout << "МатОжОп\t";
	cout << "КоэфОп\t";
	cout << "ВерОч\t";
	cout << "МатОжОч\n";
	for (int channels = 1; channels <= maxChannels; channels++)
	{
		P_0 = 0;
		MathExpectingChannels = 0;
		MathExpectingQueues = 0;
		P_queue = 0;
		loadFactorChannels = 0;
		temp = 0;
#pragma region P_0	
		for (int i = 0; i <= channels; i++)
		{
			P_0 = P_0 + powl(ro, i) / fact(i);
		}
		P_0 = P_0 + powl(ro, (long double)channels + 1) / (fact(channels) * (channels - ro));
		P_0 = 1 / P_0;
#pragma endregion

#pragma region P_n	
		P_n = P_0;
		for (int i = 1; i <= channels; ++i) {
			P_n *= ro;
			P_n /= i;
		}
#pragma endregion

#pragma region Математическое ожидание каналов
		for (int i = 1; i <= channels; ++i) {
			MathExpectingChannels += P_0 * powl(ro, i) / fact(i);
		}
		MathExpectingChannels += channels * P_n * (ro / channels) / (1 - ro / channels);
#pragma endregion

#pragma region Коэффициент загрузки операторов
		// Коэф загрузки операторов
		loadFactorChannels = MathExpectingChannels / channels;
#pragma endregion

#pragma region Вероятность очереди
		P_queue = P_n * (ro / channels) / (1 - ro / channels);
#pragma endregion

#pragma region Мат ожидание очереди
		MathExpectingQueues = P_n * (ro / channels) * (1.0L / pow(1.0L - (ro / channels), 2));
#pragma endregion

#pragma region Вывод
		cout << setprecision(5) << channels << "\t";
		cout << setprecision(5) << MathExpectingChannels << "\t";
		cout << setprecision(5) << loadFactorChannels << "\t";
		cout << setprecision(5) << P_queue << "\t";
		cout << setprecision(5) << MathExpectingQueues << "\t";

		cout << "\n";
#pragma endregion

	}
}
void Punkt4(long double maintenanceTime, long double appearanceTime, long double waitingTime, long double maxChannels)
{
	long double P_0 = 0.0;
	long double P_n = 0.0;
	long double P_queue = 0.0;
	long double MathExpectingChannels; // Мат ожидание Каналов
	long double MathExpectingQueues; // Мат ожидание очереди
	long double loadFactorChannels; // Коэф. загрузки операторов
	long double temp;
	long double ro = maintenanceTime / appearanceTime; // Коэффициент загрузки СМО
	cout << "Опер\t";
	cout << "МатОжОп\t";
	cout << "КоэфОп\t";
	cout << "ВерОч\t";
	cout << "МатОжОч\n";
	for (int channels = 1; channels <= maxChannels; channels++)
	{
#pragma region Инициализация
		P_0 = 0;
		MathExpectingChannels = 0;
		MathExpectingQueues = 0;
		P_queue = 0;
		loadFactorChannels = 0;
		temp = 0;
#pragma endregion

#pragma region P_0
		temp = Punkt4P_0(maintenanceTime, appearanceTime, waitingTime, channels, 1);
		P_0 = Punkt4P_0(maintenanceTime, appearanceTime, waitingTime, channels, 2);
		int z = 2;
		while (abs(temp - P_0) > EPS)
		{
			z++;
			temp = P_0;
			P_0 = Punkt4P_0(maintenanceTime, appearanceTime, waitingTime, channels, z);
		}
#pragma endregion

#pragma region P_n
		P_n = P_0 * powl(ro, channels) / fact(channels);
#pragma endregion

#pragma region Математическое ожидание каналов	
		temp = Punkt4MathExpectingChannels(maintenanceTime, appearanceTime, waitingTime, channels, 1, P_n, P_0);
		MathExpectingChannels = Punkt4MathExpectingChannels(maintenanceTime, appearanceTime, waitingTime, channels, 2, P_n, P_0);
		z = 2;
		while (abs(temp - MathExpectingChannels) > EPS)
		{
			z++;
			temp = MathExpectingChannels;
			MathExpectingChannels = Punkt4MathExpectingChannels(maintenanceTime, appearanceTime, waitingTime, channels, z, P_n, P_0);
		}
#pragma endregion

#pragma region Коэффициент загрузки операторов
		loadFactorChannels = MathExpectingChannels / channels;
#pragma endregion

#pragma region Вероятность очереди
		temp = Punkt4P_queue(maintenanceTime, appearanceTime, waitingTime, channels, 1, P_n, P_0);
		P_queue = Punkt4P_queue(maintenanceTime, appearanceTime, waitingTime, channels, 2, P_n, P_0);
		z = 2;
		while (abs(temp - P_queue) > EPS)
		{
			z++;
			temp = P_queue;
			P_queue = Punkt4P_queue(maintenanceTime, appearanceTime, waitingTime, channels, z, P_n, P_0);
		}
#pragma endregion

#pragma region Мат ожидание очереди
		temp = Punkt4MathExpectingQueues(maintenanceTime, appearanceTime, waitingTime, channels, 1, P_n, P_0);
		MathExpectingQueues = Punkt4MathExpectingQueues(maintenanceTime, appearanceTime, waitingTime, channels, 2, P_n, P_0);
		z = 2;
		while (abs(temp - MathExpectingQueues) > EPS)
		{
			z++;
			temp = MathExpectingQueues;
			MathExpectingQueues = Punkt4MathExpectingQueues(maintenanceTime, appearanceTime, waitingTime, channels, z, P_n, P_0);
		}
#pragma endregion

#pragma region Вывод
		cout << setprecision(5) << channels << "\t";
		cout << setprecision(5) << MathExpectingChannels << "\t";
		cout << setprecision(5) << loadFactorChannels << "\t";
		cout << setprecision(5) << P_queue << "\t";
		cout << setprecision(5) << MathExpectingQueues << "\t";

		cout << "\n";
#pragma endregion

	}
}
int main()
{
	cout.setf(ios::fixed);
	setlocale(LC_ALL, "Russian");
	long double maintenanceTime = 10; // Время обслуживания
	long double appearanceTime = 32; // Время появления заявки
	long double waitingTime = 7; // Время ожидания
	long double max = 3;
	//Punkt1(maintenanceTime, appearanceTime);
	//Punkt2(maintenanceTime, appearanceTime, max);
	//Punkt3(maintenanceTime, appearanceTime, max);
	Punkt4(maintenanceTime, appearanceTime, waitingTime, max);
	return 0;
}


