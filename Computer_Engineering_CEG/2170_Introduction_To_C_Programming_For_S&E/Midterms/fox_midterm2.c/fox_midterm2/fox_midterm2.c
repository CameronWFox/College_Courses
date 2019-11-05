/*
Author: Cameron Windsor Fox;
Midterm: 2;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_midterm2_problem1.c;
Instructor: Hutchison;
Due Date: October 31th, 2016;

Overview: This is the second midterm of this class. This will be dealing with pointers and arrays

Known Issues: None
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 5

float convertToFahrenheit(float cTemp);
void convertTemps(float fTemp, float *tempK, float *tempR);
void printTemps(float cTemp, float fTemp, float kTemp, float rTemp);
void getTemps(float tempArray[]);
void printCelsius(float tempArray[]);
int main()
{
    float cTemp = 0.0;
    float fTemp = 0.0;
    float kTemp = 0.0;
    float rTemp = 0.0;
    float *tempK = &kTemp;
    float *tempR = &rTemp;

    float tempArray[SIZE];

    printf("PART I:\n\n");
    printf("Please Enter in a Temperature value(Celsius): ");
    scanf("%f", &cTemp);
    // Methods for Part 1
    fTemp = convertToFahrenheit(cTemp);
    convertTemps(fTemp, tempK, tempR);
    printTemps(cTemp, fTemp, kTemp, rTemp);

    printf("\n\nPART II:\n");
    // Methods for Part 2
    getTemps(tempArray);
    printf("\n");
    printCelsius(tempArray);
    return 0;
}

float convertToFahrenheit(float cTemp)
{
    // Calculating the temp from C to F
    float tempF = ((cTemp * 1.8) + 32);

    return tempF;
}

void convertTemps(float fTemp, float *tempK, float *tempR)
{
    // Calculating the other temps
    float kTemp = ((fTemp + 459.67) / 1.8);
    float rTemp = (fTemp + 459.67);
    *tempK = kTemp;
    *tempR = rTemp;
}

void printTemps(float cTemp, float fTemp, float kTemp, float rTemp)
{
    // Printing the rest of the temps
    printf("\n\nOriginal Temperature: %.3f\n\n", fTemp);
    printf("Degrees in Celsius: %.3f\n", cTemp);
    printf("Degrees in Kelvin: %.3f\n", kTemp);
    printf("Degrees in Rankine: %.3f\n", rTemp);
}

void getTemps(float tempArray[])
{
    int i = 0;
    for (i = 0; i < SIZE; i++)
    {
        // Asking for user input and storing it in the array
        printf("Enter a Temperature in Celsius: ");
        scanf("%f", &tempArray[i]);
    }
}

void printCelsius(float tempArray[])
{
    int i = 0;
    float cTemp = 0.0;
    for (i = 0; i < SIZE; i++)
    {
        // Calculating and printing the input and the F calculation
        cTemp = tempArray[i];
        float fTemp = convertToFahrenheit(cTemp);
        printf("Temperature converted from C to F: %.2f C --> %.2f F\n", tempArray[i], fTemp);
    }

}
