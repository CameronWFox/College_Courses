#include <stdio.h>
/*
Author: Cameron Windsor Fox;
Lab: 2;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab2_problem1.c;
Instructor: Hutchison;
Due Date: September 9th, 2016;

Overview: This lab will be showing the amount of time it will take in minutes to cut the grass of a rectangular yard.
This lab will take input data use it for calculations and then display results of the calculations.

Known Issues:
*/

int main()
{
    // Known values

    float houseWidth;
    float houseLength;

    float yardWidth;
    float yardLength;

    float totalArea;
    float houseArea;
    float yardArea;
    float grassCutTime;

    // Rate in feet per second and feet per minute conversions
    float feetPerSecond = 2;
    float feetPerMinute = feetPerSecond * 60;

    // Input needed of the yard and the house for the calculations in feet

    printf("Enter in the HouseWidth of your choice in feet: ");
    scanf("%f", &houseWidth);
    printf("\n");

    printf("Enter in the HouseLength of your choice in feet: ");
    scanf("%f", &houseLength);
    printf("\n");

    printf("Enter in the YardWidth of your choice in feet: ");
    scanf("%f", &yardWidth);
    printf("\n");

    printf("Enter in the YardLength of your choice in feet: ");
    scanf("%f", &yardLength);
    printf("\n");

    // Calculations in feet^2 using the gathered inputs

    totalArea = (yardWidth * yardLength);
    houseArea = (houseWidth * houseLength);
    yardArea = (totalArea - houseArea);
    grassCutTime = (yardArea / feetPerMinute);

    // The results of lab2

    printf("The Area of the Yard in feet squared: %.2f\n", yardArea);
    printf("The number of minutes it takes to cut the grass is: %.1f\n", grassCutTime);
    printf("This algorithm was designed by Cameron Fox.\n");
    return 0;
}

