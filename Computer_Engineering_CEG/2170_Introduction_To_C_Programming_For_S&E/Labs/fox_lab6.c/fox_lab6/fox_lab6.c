#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159

/*
Author: Cameron Windsor Fox;
Lab: 6;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab6_problem1.c;
Instructor: Hutchison;
Due Date: October 21th, 2016;

Overview: This lab will be opening a text file and then
          use that data in calculations then display the
          results to the console

Known Issues: None
*/

// Method prototypes
void readInputFile();
void computeValues(float value1, float value2, float *sum, float *diff);
void computeProperties(float radius, float height, float *area, float *volume);
int main()
{
    float radius = 0.0;
    float height = 0.0;
    float area = 0.0;
    float volume = 0.0;

    printf(" Please Enter in a radius for a cylinder: ");
    scanf("%f", &radius);
    // Checking that the radius input is valid
    while (radius < 0)
    {
        printf(" Please Re-Enter in a radius for a cylinder(Positive Value): ");
        scanf("%f", &radius);
    }

    printf(" Please Enter in a height for a cylinder: ");
    scanf("%f", &height);
    // Checking the height input is valid
    while (height < 0)
    {
        printf(" Please Re-Enter in a height for a cylinder(Positive Value): ");
        scanf("%f", &height);
    }

    // Method being called
    computeProperties(radius, height, &area, &volume);

    // Results of the calculations from user input
    printf(" Cylinder Properties: radius = %.4f height = %.4f area = %.4f volume = %.4f\n\n", radius, height, area, volume);

    // Method being Called
    readInputFile();
    return 0;
}

void computeProperties(float radius, float height, float *area, float *volume)
{
    // Calculations
    *area = ((2 * (PI * (radius * height))) + (2 * (PI * pow(radius, 2))));
    *volume = (PI * pow(radius, 2) * height);
}

void computeValues(float value1, float value2, float *sum, float *diff)
{
    // Calculations
    *sum = (value1 + value2);
    *diff = (value1 - value2);
}

void readInputFile()
{
    int count = 0;
    int i = 0;
    FILE *fin = NULL;
    // Opens the file to be read
    fin = fopen("inputdata.txt", "r");
    fscanf(fin, "%d", &count);

    // Checks for error opening the file
    if (fin == NULL)
    {
        printf("Error Opening File!");
        exit(0);
    }

    printf(" Part III\n\n");

    // Looping through each pair of values
    for (i = 0; i < count; i++)
    {
        // Pair of numbers in the inputdata.txt file
        float value1 = 0.0;
        float value2 = 0.0;

        // Sum and Difference variables
        float sum = 0.0;
        float diff = 0.0;

        fscanf(fin, "%f %f", &value1, &value2);
        computeValues( value1, value2, &sum, &diff);
        // Prints the data out to the console
        printf(" NUM1: %.4f NUM2: %2.4f SUM: %2.4f DIFF: %2.4f\n", value1, value2, sum, diff);
    }

    // Closes the file
    fclose(fin);
}
