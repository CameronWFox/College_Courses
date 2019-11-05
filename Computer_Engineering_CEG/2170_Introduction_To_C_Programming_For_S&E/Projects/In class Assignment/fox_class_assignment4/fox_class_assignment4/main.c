#include <stdio.h>
#include <stdlib.h>
#define max 5

int main()
{
    float testScore = 0.0;
    float sum = 0.0;
    float highestTestScore = 0.0;
    float smallestTestScore = 100;
    int count = 0;

    // For Loop Example
    for (count = 0; count < max; count++)
    {
        printf("Please enter in a test score: ");
        scanf("%f", &testScore);
        sum = sum + testScore;
        if (testScore > highestTestScore)
        {
            highestTestScore = testScore;
        }

        if (testScore < smallestTestScore)
        {
            smallestTestScore = testScore;
        }
    }
    printf("The average of the test scores is:%.2f \n ", (sum / max));
    printf("The largest Test Score is:%.2f \n", highestTestScore);
    printf("The smallest Test Score is:%.2f \n", smallestTestScore);


    // While Loop Example
        while (count < max)
    {
        printf("Please enter in a test score: ");
        scanf("%f", &testScore);
        sum = sum + testScore;
        if (testScore > highestTestScore)
        {
            highestTestScore = testScore;
        }

        if (testScore < smallestTestScore)
        {
            smallestTestScore = testScore;
        }
        count++;
    }
    printf("The average of the test scores is:%.2f \n ", (sum / max));
    printf("The largest Test Score is:%.2f \n", highestTestScore);
    printf("The smallest Test Score is:%.2f \n", smallestTestScore);

    // Do While Loop Example
        do
    {
        printf("Please enter in a test score: ");
        scanf("%f", &testScore);
        sum = sum + testScore;
        if (testScore > highestTestScore)
        {
            highestTestScore = testScore;
        }

        if (testScore < smallestTestScore)
        {
            smallestTestScore = testScore;
        }
        count++;
    }
    while (count < max);

    printf("The average of the test scores is:%.2f \n ", (sum / max));
    printf("The largest Test Score is:%.2f \n", highestTestScore);
    printf("The smallest Test Score is:%.2f \n", smallestTestScore);

    return 0;
}
