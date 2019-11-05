#include <stdio.h>
#include <conio.h>

/*
Author: Cameron Windsor Fox;
Midterm: 1;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_midterm1_problem1.c;
Instructor: Hutchison;
Due Date: October 7th, 2016;

Overview: This project will be using two different types of loops and prompt the user for input
        in two different ways. Then output the total of all the data added together for each different loop.

Known Issues: None
*/

void checkPrice(float walmartPrice, float amazonPrice, float targetPrice);
float computeAverage(float walmartPrice, float amazonPrice, float targetPrice);

int main()
{
    float walmartPrice = 0.0;
    float amazonPrice = 0.0;
    float targetPrice = 0.0;
    char userChoice = 'z';

    // Input from user
    do
    {
    printf("\n\n Enter a price from Walmart: ");
    scanf("%f", &walmartPrice);

    printf(" Enter a price from Amazon: ");
    scanf("%f", &amazonPrice);

    printf(" Enter a price from Target: ");
    scanf("%f", &targetPrice);

    // Methods called
    checkPrice(walmartPrice, amazonPrice, targetPrice);
    computeAverage(walmartPrice, amazonPrice, targetPrice);
    float average = computeAverage(walmartPrice, amazonPrice, targetPrice);
    printf("The average of the three prices is: %.2f\n", average);


    printf("\n Do you want to run this program again?: ");
    userChoice = getche();

    }
    while(userChoice == 'y' || userChoice == 'Y');

    return 0;
}

void checkPrice(float walmartPrice, float amazonPrice, float targetPrice)
{
    if (walmartPrice < amazonPrice && walmartPrice < targetPrice)
    {
        printf("The Walmart price is the best deal!!\n");

    }
    else if (amazonPrice < walmartPrice && amazonPrice < targetPrice)
    {
        printf("The Amazon price is the best deal!!\n");

    }
    else if (targetPrice < walmartPrice && targetPrice < amazonPrice)
    {
        printf("The Target price is the best deal!!\n");

    }
}

float computeAverage(float walmartPrice, float amazonPrice, float targetPrice)
{
    return ((walmartPrice + amazonPrice + targetPrice) / 3);
}
