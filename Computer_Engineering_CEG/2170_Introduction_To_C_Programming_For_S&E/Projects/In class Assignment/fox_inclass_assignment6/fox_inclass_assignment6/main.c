#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ELMS 11

void fillArrays(int valueSquare[], int valueCubed[]);
void printArrays(int valueSquare[], int valueCubed[]);
int main()
{
    int valueSquare[MAX_ELMS];
    int valueCubed[MAX_ELMS];

    fillArrays(valueSquare, valueCubed);
    printArrays(valueSquare, valueCubed);

    return 0;
}

void fillArrays(int valueSquare[], int valueCubed[])
{
    int i = 0;

    for (i = 0; i < MAX_ELMS; i++)
    {
        valueSquare[i] = i * i;
        valueCubed[i] = i * i * i;
    }
}

void printArrays(int valueSquare[], int valueCubed[])
{
    int i = 0;

    for (i = 0; i < MAX_ELMS; i++)
    {
    printf("%d ", valueSquare[i]);
    }

    printf("\n\n");

    for (i = 0; i < MAX_ELMS; i++)
    {
    printf("%d ", valueCubed[i]);
    }
}
