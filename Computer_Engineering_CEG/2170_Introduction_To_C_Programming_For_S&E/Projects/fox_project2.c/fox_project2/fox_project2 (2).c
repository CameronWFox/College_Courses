#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define gravityConstant 32.17
#define PI 3.14159

#define ERROR -1

#define Nylon 1.15
#define Aluminum 2.70
#define Titanium 4.50
#define Steel 7.87
#define Brass 8.75

/*
Author: Cameron Windsor Fox;
Project: 2;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_project2_problem1.c;
Instructor: Hutchison;
Due Date: September 27th, 2016;

Overview: This Project will be using formulas and user input for calculations and calling multiple methods within functions

Known Issues: None
*/
void implementPart1();
float computeDuration(float velocity, float angle, float distance);
float computeHeight(float velocity, float angle, float time);

void implementPart2();
float computeRimArea(float outerRimDiameter, float innerRimDiameter);
float computeVolume(float area, float thickness);
float computeWeight(float volume);
int main()
{
    implementPart1();
    implementPart2();
    return 0;
}

void implementPart1()
{
    float initialVelocity;
    float elevationAngle;
    float targetDistance;
    float angleRadians;

    printf("Part 1 of Project2: \n\n");

    // Prompting the user for input
    printf("Please enter a Initial Velocity (f/s): ");
    scanf("%f", &initialVelocity);

    printf("Please enter the elevation angle (degrees): ");
    scanf("%f", &elevationAngle);

    printf("Please enter the distance from the target (feet): ");
    scanf("%f", &targetDistance);


    // First convert the elevationAngle from degrees to radians
    angleRadians = elevationAngle * (PI / 180);


    // Calculations for the timeDuration and height
    float timeDuration = (targetDistance / (initialVelocity * cos(angleRadians)));

    float height = (initialVelocity * timeDuration * sin(angleRadians)) - (gravityConstant * pow(timeDuration, 2)) / 2;

    // Functions called for implementPart1
    computeDuration(initialVelocity, angleRadians, targetDistance);
    computeHeight(initialVelocity, angleRadians, timeDuration);



    // An If else statement to check if the height value is acceptable
    if (height >= 0)
    {
        printf("The height calculated comes out to be: %.2f feet", height);
        printf("\n\n");
    }
    else
    {
        printf(" The Height Result is Not Allowed!! Please Re-Run the Program!");
        printf("\n\n");
    }

}

float computeDuration(float velocity, float angle, float distance)
{
    float timeDuration;

    // Formula used for the calculation in this function
    timeDuration = (distance / (velocity * cos(angle)));

    printf("The timeDuration calculated comes out to be: %.2f seconds", timeDuration);
    printf("\n");

    return timeDuration;
}

float computeHeight(float velocity, float angle, float time)
{
    float height;

    // Formula for the calculation used in this function
    height = (velocity * time * sin(angle)) - (gravityConstant * pow(time, 2)) / 2;

    return height;
}

void implementPart2()
{
    float washerOutRim;
    float washerInRim;
    float washerThickness;
    float washerQuantity;



    printf("Part 2 of Project2: \n\n");

    // Prompting the user for input
    printf("please enter the Washer Outer Rim Diameter (cm): ");
    scanf("%f", &washerOutRim);

    printf("Please enter the Washer Inner Rim Diameter (cm): ");
    scanf("%f", &washerInRim);

    printf("Please enter the Thickness of the Washer (cm): ");
    scanf("%f", &washerThickness);

    printf("Please enter the Washer Quantity: ");
    scanf("%f", &washerQuantity);



    // Calculations for the rim area
    float rimArea;

    rimArea = (PI * pow((washerOutRim / 2), 2)) - (PI * pow((washerInRim / 2), 2));

    // Calculations for the washer weight
    float washerVolume;

    washerVolume = (rimArea * washerThickness);

    float totalWasherWeight;

    totalWasherWeight = (computeWeight(washerVolume) * washerQuantity);

    printf("The washer weight of the washers is:%.2f ", totalWasherWeight);


    // Functions called for implementPart2
    computeRimArea(washerOutRim, washerInRim);
    computeVolume(rimArea, washerThickness);

}



float computeRimArea(float outerRimDiameter, float innerRimDiameter)
{
    // Computing the area
    float rimArea;

    rimArea = (PI * pow((outerRimDiameter / 2), 2)) - (PI * pow((innerRimDiameter / 2), 2));

    return rimArea;
}

float computeVolume(float area, float thickness)
{
    // Computing the volume
    float washerVolume;

    washerVolume = (area * thickness);

    return washerVolume;
}

float computeWeight(float volume)
{
    char washerSelection;
    float washerWeight;

    printf("Please Enter the Washer Material you want: \n\n");

    printf("N - Nylon \n");
    printf("A - Aluminum \n");
    printf("T - Titanium \n");
    printf("S - Steel \n");
    printf("B - Brass \n\n");

    // Asking for input
    printf("Enter your Selection Here: ");
    fflush(stdin);
    scanf("%c", &washerSelection);


    // Check if input is valid
    if (washerSelection == 'N')
    {
        washerWeight = (Nylon * volume);
        printf("The weight of a single washer made from Nylon is:%.2f \n\n", washerWeight);

    }
    else if (washerSelection == 'A')
    {
        washerWeight = (Aluminum * volume);
        printf("The weight of a single washer made from Aluminum is:%.2f \n\n", washerWeight);

    }
    else if(washerSelection == 'T')
    {
        washerWeight = (Titanium * volume);
        printf("The weight of a single washer made from Titanium is:%.2f \n\n", washerWeight);

    }
    else if(washerSelection == 'S')
    {
        washerWeight = (Steel * volume);
        printf("The weight of a single washer made from Steel is:%.2f \n\n", washerWeight);

    }
    else if(washerSelection == 'B')
    {
        washerWeight = (Brass * volume);
        printf("The weight of a single washer made from Brass is:%.2f \n\n", washerWeight);

    }
    else
    {
        printf("ERROR: Invalid Character Entered! Re-Run Program!!");
    }


    return washerWeight;
}

