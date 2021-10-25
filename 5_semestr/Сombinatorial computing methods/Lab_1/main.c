#include <stdio.h>
#define N 7


void printPath(int array[]) {
    for (int i = 0; i < N; i++) {
        if (array[i] == 1) {
            printf("%s", "H"); //Horizontal step
        }
        if (array[i] == 0) {
            printf("%s", "V"); //Vertical step
        }
    }
    putchar('\n');
}

void leftShiftTransposition(int array[]) {
    int flag = 1;
    while (flag)    // exit when do not search 01  
    { 
        flag = 0;
        for (int i = 0; i < N - 1; i++) {
            if (array[i] == 0 && array[i + 1] == 1) // Search 01
            { 
                flag = 1;

                array[i] = 1;       // Replace 01 by 10
                array[i + 1] = 0; 

                printPath(array);

                if (i > 1) 
                {
                    int k = 1;
                    for (int j = i - 2; j >= 0; j--) // Shift group of 1 in high digits to 10
                    {  
                        if (array[j] == 1 && array[j + 1] == 0) 
                        {
                            array[i - k] = 1;
                            array[j] = 0;
                            k++;
                        }
                    }
                }
                break; //escape from loop for when transposition step completed
            }
        }
    }
}

int main() {
    int binaryCombinations[N] = { 0, 0, 0, 0, 1, 1, 1 }; // 4 vertical steps, 3 horizontal step
    printPath(binaryCombinations); // first combination

    leftShiftTransposition(binaryCombinations); //Left Shift Transposition

    return 0;
}
