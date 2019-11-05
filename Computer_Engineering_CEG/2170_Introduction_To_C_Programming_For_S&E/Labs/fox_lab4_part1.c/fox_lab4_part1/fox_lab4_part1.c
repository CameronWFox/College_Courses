#include <stdio.h>

/*
Author: Cameron Windsor Fox;
Lab: 4 Part 1;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab4_problem1.c;
Instructor: Hutchison;
Due Date: September 30th, 2016;

Overview: This program is all about using if/else/if statements. To show the different types of earthquakes
          and the damage the each level can do. Based on what level the user inputs.

Known Issues: None
*/

void characterize_earthquake( double magnitude);
int main()
{
    double magnitude;
//get the magnitude of the earthquake from the user
    printf("Enter the magnitude level from 1 - 10: ");
    scanf("%lf", &magnitude);
//call the characterize earthquake function here
    characterize_earthquake( magnitude);
    return 0;
}

/****************************************************************************
This function displays the effects of an earthquake based on the Richer Scale
Input parameters: magnitude is a value between 1 and 10
Return: none
*****************************************************************************
*****/
void characterize_earthquake( double magnitude)
{
    // All the different types of earthquakes and what each different level stands for
    if (magnitude >= 1.0 && magnitude <= 1.9)
    {
        printf("Microearthquakes, not felt, or felt rarely.\n");
        printf("Recorded by seismographs.");
    }
    else if (magnitude >= 2.0 && magnitude <= 2.9)
    {
        printf("Felt slightly by some people.\n");
        printf("No damage to buildings.");
    }
    else if (magnitude >= 3.0 && magnitude <= 3.9)
    {
        printf("Often felt by people, but very rarely causes damage.\n");
        printf("Shaking of indoor objects can be noticeable.");
    }
    else if (magnitude >= 4.0 && magnitude <= 4.9)
    {
        printf("Noticeable shaking of indoor objects and rattling noises.\n");
        printf("Felt by most people in the affected area. Slightly felt outside.\n");
        printf("Generally causes none to minimal damage.\n");
        printf("Moderate to significant damage very unlikely.\n");
        printf("Some objects may fall off shelves or be knocked over.");
    }
    else if (magnitude >= 5.0 && magnitude <= 5.9)
    {
        printf("Can cause damage of varying severity to poorly constructed buildings.\n");
        printf("At most, none to slight damage to all other buildings. Felt by everyone.");
    }
    else if (magnitude >= 6.0 && magnitude <= 6.9)
    {
        printf("Damage to a moderate number of well-built structures in populated areas.\n");
        printf("Earthquake-resistant structures survive with slight to moderate damage.\n");
        printf("Poorly designed structures receive moderate to severe damage.\n");
        printf("Felt in wider areas; up to hundreds of miles/kilometers from the epicenter.\n");
        printf("Strong to violent shaking in epicentral area.");
    }
    else if (magnitude >= 7.0 && magnitude <= 7.9)
    {
        printf("Causes damage to most buildings, some to partially or completely collapse or receive severe damage.\n");
        printf("Well-designed structures are likely to receive damage.\n");
        printf("Felt across great distances with major damage mostly limited to 250 km from epicenter.");
    }
    else if (magnitude >= 8.0 && magnitude <= 8.9)
    {
        printf("Major damage to buildings, structures likely to be destroyed.\n");
        printf("Will cause moderate to heavy damage to sturdy or earthquake-resistant buildings.\n");
        printf("Damaging in large areas. Felt in extremely large regions.");
    }
    else if (magnitude >= 9.0 && magnitude <= 10.0)
    {
        printf("At or near total destruction - severe damage or collapse to all buildings.\n");
        printf("Heavy damage and shaking extends to distant locations.\n");
        printf("Permanent changes in ground topography.");
    }

    // If the user enters a level that is to high or to low for the different levels of earthquakes
    else
    {
        printf("The magnitude level you entered is not valid, please try again.");
    }
}

