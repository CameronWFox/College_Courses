#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define PI 3.14159

/*
Author: Cameron Windsor Fox;
Project: 4;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_project4_problem1.c;
Instructor: Hutchison;
Due Date: October 25th, 2016;

Overview: This program calculates the change in metal based on the change in the metal poles starting length
          and the beginning and final temperature change.

Known Issues: None
*/
int getMetalID();
void getData(FILE *fin, int metalID, float *A, float *B, int *highTemp, int *lowTemp);
float getInitialLength();
float getFinalTemperature(int metalID, int *lowTemp, int *highTemp);
float getExpandedLength(float initialLength, float *A, float *B, float finalTemp);
void printReport(int metalID, float initialTemp, float initialLength, float finalTemp, float finalLength);
int main()
{
    FILE *fin = NULL;
    float A = 0.0;
    float B = 0.0;
    int lowTemp = 0;
    int highTemp = 0;
    float initialTemp = 32.00;
    char userChoice = 'z';
    do
    {
        // Methods called
        int metalID = getMetalID();
        getData(fin, metalID, &A, &B, &lowTemp, &highTemp);
        float initialLength = getInitialLength();
        float finalTemp = getFinalTemperature(metalID, &lowTemp, &highTemp);
        float finalLength = getExpandedLength(initialLength, &A, &B, finalTemp);
        printReport(metalID, initialTemp, initialLength, finalTemp, finalLength);




        // Check if the user wants to re-run the program
        printf("\n Would you like to re-run this program again?: ");
        userChoice = getche();

    }
    while (userChoice == 'y' || userChoice == 'Y');

    return 0;
}

int getMetalID()
{
    int metalID;
    // Getting the metalID from user
    printf("Please Enter A MetalID (1 - 7)\n\n");
    printf("1 - Aluminum\n");
    printf("2 - Cast Iron\n");
    printf("3 - Ingot Iron\n");
    printf("4 - Malleable Iron\n");
    printf("5 - Ingot Steel\n");
    printf("6 - Copper\n");
    printf("7 - Nickel\n\n");
    printf("Enter Your MetalID: ");
    scanf("%d", &metalID);

    // Checking the input from user is valid
    while (metalID < 1 || metalID > 7)
    {
        printf("Please Re- Enter A Valid MetalID (1 - 7)\n\n");
        printf("1 Aluminum\n");
        printf("2 Cast Iron\n");
        printf("3 Ingot Iron\n");
        printf("4 Malleable Iron\n");
        printf("5 Ingot Steel\n");
        printf("6 Copper\n");
        printf("7 Nickel\n\n");
        printf("Enter Your MetalID: ");
        scanf("%d", &metalID);
    }
    return metalID;
}

void getData(FILE *fin, int metalID, float *A, float *B, int *lowTemp, int *highTemp)
{
    int i = 0;
    int ID = 0;

    // Opens the input file
    fin = fopen("input.txt", "r");

    // Error checks opening the input file
    if (fin == NULL)
    {
        printf("ERROR OPENING FILE!!");
        exit(0);
    }

    // Gathers the data on the metal based on the user entered metalID
    for (i = 0; i < 7; i++)
    {
        fscanf(fin, "%d %f %f %d %d", &ID, A, B, lowTemp, highTemp);

        if (metalID == ID)
        {
        break;
        }
    }
    fclose(fin);
}

float getInitialLength()
{
    float initialLength = 0.0;
    printf("Please enter the starting length of the metal(inches): ");
    scanf("%f", &initialLength);
    while (initialLength <= 0)
    {
        printf("Please enter a valid starting length of the metal(Greater than zero!): ");
        scanf("%f", &initialLength);
    }
    return initialLength;
}

float getFinalTemperature(int metalID, int *lowTemp, int *highTemp)
{
    float finalTemp = 0.0;
    printf("Please enter in the final Temperature value (nearest tenth degree in Fahrenheit): ");
    scanf("%f", &finalTemp);
    while (finalTemp < *lowTemp || finalTemp > *highTemp)
    {
        printf("Please enter a valid final temperature of the metal(Within the low and high temp limit!): ");
        scanf("%f", &finalTemp);
    }

    return finalTemp;
}

float getExpandedLength(float initialLength, float *A, float *B, float finalTemp)
{
    float expandedLength = (initialLength * (1 + (*A * (((finalTemp - 32.0) / 1000.0)) + (*B * pow(((finalTemp - 32.0) / 1000.0), 2)))));
    return expandedLength;
}

void printReport(int metalID, float initialTemp, float initialLength, float finalTemp, float finalLength)
{
    printf("Metal ID = %d\n", metalID);

    if (metalID == 1)
    {
        printf("Metal Name = Aluminum\n");
    }
    else if (metalID == 2)
    {
        printf("Metal Name = Cast Iron\n");
    }
    else if (metalID == 3)
    {
        printf("Metal Name = Iron Ingot\n");
    }
    else if (metalID == 4)
    {
        printf("Metal Name = Malleable Iron\n");
    }
    else if (metalID == 5)
    {
        printf("Metal Name = Ingot Steel\n");
    }
    else if (metalID == 6)
    {
        printf("Metal Name = Copper\n");
    }
    else if (metalID == 7)
    {
        printf("Metal Name = Nickel\n");
    }

    printf("Initial Temperature = %.2f\n", initialTemp);
    printf("Initial Length = %.6f\n", initialLength);
    printf("Final Temperature = %.2f\n", finalTemp);
    printf("Final Length = %.6f\n", finalLength);
}
