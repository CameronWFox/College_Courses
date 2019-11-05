#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Author: Cameron Windsor Fox;
Lab: 9;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab9_problem1.c;
Instructor: Hutchison;
Due Date: November 18th, 2016;

Overview: This Lab used typedef functions and gathering input from user
          and then using the typedef functions to create points and the length of a line segment
          then finally calculating the length of the line segment with the starting and ending points

Known Issues: None
*/

// typedef for float points
typedef struct
{
    float x;
    float y;
} Point;

// typedef for line segment
typedef struct
{
    Point start;
    Point end;
} LineSegment;
// Prototypes
void displayPoint( Point coordinate);
void displayLineSegment( LineSegment line);
double calculateLength( LineSegment line);
int main()
{
    // Variables from the typedef functions
    Point p1;
    Point p2;
    Point coordinate;
    LineSegment line;

    // Getting input from the user
    printf("Please Enter the x value for the point p1: ");
    scanf("%f", &p1.x);

    printf("Please Enter the y value for the point p1: ");
    scanf("%f", &p1.y);

    // Setting the first set of points
    coordinate.x = p1.x;
    coordinate.y = p1.y;
    displayPoint( coordinate);
    line.start = coordinate;

    printf("Please Enter the x value for the point p2: ");
    scanf("%f", &p2.x);

    printf("Please Enter the y value for the point p2: ");
    scanf("%f", &p2.y);

    // Setting the second set of points
    coordinate.x = p2.x;
    coordinate.y = p2.y;
    displayPoint( coordinate);
    line.end = coordinate;

    // Method calls
    displayLineSegment( line);
    double calculation = calculateLength( line);

    // Printing the result of the calculated length
    printf("The calculated length from the points given by the user is: %.3lf\n\n", calculation);
    return 0;

}

void displayPoint( Point coordinate)
{
    // Displaying the point variable by using the input from the user
    printf("\nThe Point gathered from the user is (%.2f, %.2f)\n",coordinate.x, coordinate.y);
}

void displayLineSegment( LineSegment line)
{
    // Displays the line segment
    printf("\nThe line segment \nStarts at:(%.2f, %.2f) \nEnds at: (%.2f, %.2f)\n\n", line.start.x, line.start.y, line.end.x, line.end.y);

}

double calculateLength( LineSegment line)
{
    // Does the length calculation by using input from the user
    double length = sqrt(pow((line.end.x - line.start.x), 2) + pow((line.end.y - line.start.y), 2));
    return length;
}
