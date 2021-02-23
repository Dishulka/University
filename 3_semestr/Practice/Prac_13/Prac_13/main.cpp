/*Требуется составить ООП для получения любого начального фрагмента последовательности Хэмминга
из целых чисел, которые не имеют других простых делителей кроме 2,3 и 5. При этом последовательность
должна рождаться в порядке роста значений её элементов без тотальной проверки делимости всех чисел
или вычисления степеней делителей. Количество элементов должен задавать аргумент командной строки
вызова программы. Результат вычислений должен отображаться через поток стандартного вывода, где для каждого
элемента указан элемент, из которого он получен.
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Hamming
{
private:
    vector<int> sequence;
    int amount;
public:
    Hamming(int n = 0) : amount(n) {};
    void seqHamming();
    void print_seq();
};


void Hamming::print_seq(void)
{
    for (int i = 0; i < sequence.size(); ++i)
        cout << sequence[i] << ' ';
}


void Hamming::seqHamming()
{
    priority_queue<int, vector<int>, greater<int>> priorQueue;
    priorQueue.push(2);
    priorQueue.push(3);
    priorQueue.push(5);
    priorQueue.push(7);

    int n = amount;
    while (n != 0) {
        int elem = priorQueue.top();

        while (priorQueue.top() == elem)
            priorQueue.pop();

        sequence.push_back(elem);

        priorQueue.push(elem * 2);
        priorQueue.push(elem * 3);
        priorQueue.push(elem * 5);
        priorQueue.push(elem * 7);

        --n;
    }
}


int main()
{
    cout << "Amount of elements = ";
    int n;
    cin >> n;

    Hamming hamming(n);
    hamming.seqHamming();
    hamming.print_seq();

    return 0;
}