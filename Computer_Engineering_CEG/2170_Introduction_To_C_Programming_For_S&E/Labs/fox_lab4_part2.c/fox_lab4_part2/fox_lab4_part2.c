#include <stdio.h>

/*
Author: Cameron Windsor Fox;
Lab: 4 Part 2;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab4_problem2.c;
Instructor: Hutchison;
Due Date: September 30th, 2016;

Overview: This program will be doing the same function using if/else/if and then doing it gain using switch statements

Known Issues: None
*/


void report_container_contents_if( char color);
void report_container_contents_switch( char color);
int main()
{
    char color;
    printf( "Enter the color of the container, as a single letter from the following colors\n");

    // This shows the different colors to pick from and lets the user know and upper and lower case do not matter
    printf(" o - Orange ");
    printf(" O - Orange\n\n");
    printf(" b - Blue ");
    printf(" B - blue\n\n");
    printf(" y - Yellow ");
    printf(" Y - Yellow\n\n");
    printf(" g - Green ");
    printf(" G - Green\n\n");

    // We prompt the user to enter a letter for a color choice
    printf("Please enter your color choice: ");
    scanf( "%c", &color);

    // The two methods that are being called
    report_container_contents_if( color);
    report_container_contents_switch( color);
    return 0;
}

/****************************************************************************
This function displays the contents of a container based on the container's
color:
 O (orange) is ammonia; B (brown) is carbon monoxide;
 Y (yellow) is hydrogen; G (green) is oxygen.
All other letters indicate unknown color/unknown contents
Input parameters: color – the color of the container
Return: none
****************************************************************************/
void report_container_contents_if( char color)
{
    // This function will print out information based on the color choice of the user
    if (color == 'o' || color == 'O')
    {
        printf("The contents of the container is ammonia.\n");
    }
    else if (color == 'b' || color == 'B')
    {
        printf("The contents of the container is carbon monoxide.\n");
    }
    else if (color == 'y' || color == 'Y')
    {
        printf("The contents of the container is hydrogen.\n");
    }
    else if (color == 'g' || color == 'G')
    {
        printf("The contents of the container is oxygen.\n");
    }

    // This result happens if the user enters a color that is not from the colors listed above
    else
    {
        printf("This is an Unknown color and the contents is Unknown.\n");
    }
}

/****************************************************************************
This function displays the contents of a container based on the container's
color:
 O (orange) is ammonia; B (brown) is carbon monoxide;
 Y (yellow) is hydrogen; G (green) is oxygen.
All other letters indicate unknown color/unknown contents
Input parameters: color – the color of the container
Return: none
****************************************************************************/
void report_container_contents_switch( char color)
{
    // This code will be doing the same process as before but will use switch statements
    switch (color)
    {
    case 'o':
    case 'O':

        printf("The contents of the container is ammonia.\n");
        break;

    case 'b':
    case 'B':

        printf("The contents of the container is carbon monoxide.\n");
        break;

    case 'y':
    case 'Y':

        printf("The contents of the container is hydrogen.\n");
        break;

    case 'g':
    case 'G':

        printf("The contents of the container is oxygen.\n");
        break;

        // This result happens if the user enters a color that is not from the colors listed above
    default:

        printf("This is an Unknown color and the contents is Unknown.\n");
        break;

    }
}

