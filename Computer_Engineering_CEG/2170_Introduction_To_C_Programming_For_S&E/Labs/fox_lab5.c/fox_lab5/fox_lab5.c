#include <stdio.h>

/*
Author: Cameron Windsor Fox;
Lab: 5;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab5_problem1.c;
Instructor: Hutchison;
Due Date: October 7th, 2016;

Overview: This project will be using two different types of loops and prompt the user for input
        in two different ways. Then output the total of all the data added together for each different loop.

Known Issues: None
*/

// Method Prototypes
void testWhileLoop();
void testForLoop();

int main ()
{
    // Asking user for input
    printf("While Loop Test: \n\n");
    testWhileLoop();

    printf("For Loop Test: \n\n");
    testForLoop();

    return 0;
}

void testWhileLoop()
{
    int count = 0;
    int totalWSum = 0;
    int valueEntered;

    // While Loop for this Function
    while (count < 10)
    {
        // Asking user for a value from 5 to 20
        printf("Please enter in a value (From 5 to 20): ");
        scanf("%d", &valueEntered);

        // Checking that the User Input is valid
        while (valueEntered < 5 || valueEntered > 20)
        {
            printf("You Entered an Invalid number!! Please Re-Enter: ");
            scanf("%d", &valueEntered);
        }
        printf(" Value Entered:%d \n", valueEntered);

        totalWSum = valueEntered + totalWSum;

        count++;
    }
    // Printing the total
    printf("The Total Sum is:%d \n\n\n\n", totalWSum);


}

void testForLoop()
{
    int count = 0;
    int totalFSum = 0;
    int valueEntered;

    // For Loop for this Function
    for (count = 0; count < 10; count++)
    {
        // Asking a user for a number value of any integer
        printf("Please enter in a value: ");
        scanf("%d", &valueEntered);

        printf(" Value Entered:%d \n", valueEntered);

        totalFSum = valueEntered + totalFSum;

    }
    // Printing the total
    printf("The Total Sum is:%d \n\n\n\n", totalFSum);


}

