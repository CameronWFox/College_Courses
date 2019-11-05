#include <stdio.h>
#include <math.h>
/*
Author: Cameron Windsor Fox;
Lab: 3 part1;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab3_problem1.c;
Instructor: Hutchison;
Due Date: September 23th, 2016;

Overview: This project will will be output the results for each of the following statements listed from
the rubric.

Known Issues: None
*/
int main()
{
    // These are the different expressions that are given and the results are displayed as output.
    printf("Expression a = %f \n", ceil(16.2));
    printf("Expression b = %f \n", floor(-7.5)*pow(3.0,2.0));
    printf("Expression c = %f \n", sqrt(ceil(fabs(-7.4))));
    printf("Expression d = %f \n", sqrt(3 + 13)*pow(5,2));
    printf("Expression e = %f \n", sqrt(pow((12 -3),3)));

    printf(" This algorithm was designed by Cameron Fox.");
    return 0;
}
