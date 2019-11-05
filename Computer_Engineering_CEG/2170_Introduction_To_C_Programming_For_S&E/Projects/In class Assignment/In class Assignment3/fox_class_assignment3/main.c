#include <stdio.h>
#include <stdlib.h>

int main()
{
    float numA, numB, numC, numD;
    float sum;
    printf("please enter in the first floating point number: ");
    scanf("%f", &numA);

    printf("please enter in the second floating point number: ");
    scanf("%f", &numB);

    printf("please enter in the third floating point number: ");
    scanf("%f", &numC);

    printf("please enter in the fourth floating point number: ");
    scanf("%f", &numD);

    sum = numA + numB + numC + numD;


    if (sum > 0.0)
    {
        float numAverage = (sum / 4);
        printf("The average of the numbers entered is:%.2f ", numAverage);
    }
    else
    {
        printf("The average is less than 0.0, please enter in different numbers!");
    }
    return 0;
}
