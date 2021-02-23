/*��������� ��������� ��� ��� ��������� ������ ���������� ��������� ������������������ ��������
�� ����� �����, ������� �� ����� ������ ������� ��������� ����� 2,3 � 5. ��� ���� ������������������
������ ��������� � ������� ����� �������� � ��������� ��� ��������� �������� ��������� ���� �����
��� ���������� �������� ���������. ���������� ��������� ������ �������� �������� ��������� ������
������ ���������. ��������� ���������� ������ ������������ ����� ����� ������������ ������, ��� ��� �������
�������� ������ �������, �� �������� �� �������.
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
    void Ham();
    void print_seq();
};


void Hamming::print_seq(void)
{
    for (int i = 0; i < sequence.size(); ++i)
        cout << sequence[i] << ' ';
}


void Hamming::Ham()
{
    vector<int> tempSeq;
    tempSeq.push_back(5);
    tempSeq.push_back(3);
    tempSeq.push_back(2);

    int n = amount;
    while (n != 0) {
        int elem = tempSeq.back();

        while (tempSeq.back() == elem)
            tempSeq.pop_back();

        sequence.push_back(elem);

        tempSeq.push_back(elem * 2);
        tempSeq.push_back(elem * 3);
        tempSeq.push_back(elem * 5);

        sort(tempSeq.rbegin(), tempSeq.rend());

        --n;
    }
}


int main()
{
    cout << "Amount of elements = ";
    int n;
    cin >> n;

    Hamming hamming(n);
    hamming.Ham();
    hamming.print_seq();

    return 0;
}