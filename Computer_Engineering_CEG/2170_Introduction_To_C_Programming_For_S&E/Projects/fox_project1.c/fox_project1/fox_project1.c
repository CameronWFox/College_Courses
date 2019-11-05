#include <stdio.h>
#include <math.h>
/*
Author: Cameron Windsor Fox;
Project: 1;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_project1_problem1.c;
Instructor: Hutchison;
Due Date: September 13th, 2016;

Overview: This project will be gathering input from the user and using it to calculate the volume of two different shapes.
We will also be using three different formulas for this project.

Known Issues:
*/
int main()
{
    // Known values

    // Values for the first formula
    float angle;
    float radius1;

    // Values used for the second and third formulas
    float slantHeight;
    float radius2;
    double PI = 3.141592654;

    // The three different formulas that will be used in the project
    float sphericalWedgeVolume;
    float rightCircularConeVolume;
    float height;


    // Prompting the user for data to be used for calculations of the first formula
    printf("Please enter in the radius of your choosing: ");
    scanf("%f", &radius1);
    printf("\n");

    printf("Please enter in the degrees of the angle of your choosing: ");
    scanf("%f", &angle);
    printf("\n");

    // The results from the first formula that is used in this project from the data given by the user
    sphericalWedgeVolume = ((2.0/3.0)*(pow(radius1, 3)*angle));


    // The results of the first formula used in this project
    printf("The volume of the first formula given: %.2f", sphericalWedgeVolume);
    printf("\n");


    // Prompting the user for data to be used for calculations of the second formula and the third formula
    printf("Please enter in another radius of your choosing: ");
    scanf("%f", &radius2);
    printf("\n");

    printf("Please enter in the slantHeight of your choosing: ");
    scanf("%f", &slantHeight);
    printf("\n");


    // The results from the second formula and third formula that is used in this project from the data given by the user
    height = (pow(slantHeight, 2) - pow(radius2, 2));

    rightCircularConeVolume = ((1.0/3.0)*(PI*pow(radius2, 2) * height));


    // The results of the remaining formulas used in this program
    printf("The volume of the second formula given: %.2f", rightCircularConeVolume);
    printf("\n");

    printf("This algorithm was designed by Cameron Fox.");
    printf("\n");

    return 0;

}
