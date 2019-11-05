#include <stdio.h>
#include <math.h>
#define PI 3.14159

/*
Author: Cameron Windsor Fox;
Lab: 3 part2;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab3_problem2.c;
Instructor: Hutchison;
Due Date: September 23th, 2016;

Overview: This project will give us a function that is already partly completed and our job is to fill in the missing code
          in the following section:

                Calling the calc_cost function in main
                Filling in code for the calc_surface_area function
                Filling in comments of the calc_cost function
                The last step is to fill in the code for the display_results function

           That is all that is instructed to be done in the lab3 part 2 assignment.

Known Issues: None
*/

float calc_surface_area( float radius, float height);
float calc_cost( float surface_area, float cost_per_sq_cm);
void display_results( float radius, float height, float cost_per_sq_cm, int quantity,
                      float surface_area, float cost_per_container, float total_cost);

int main()
{
    float radius, height, cost_per_sq_cm;
    int quantity;
    float surface_area, cost_per_container, total_cost;

    //input container dimensions, material cost, quantity
    printf("Enter the radius of the container's base: ");
    scanf( "%f", &radius);
    printf( "Enter the height of the container: ");
    scanf( "%f", &height);
    printf( "Enter the material's cost per square centimeter: ");
    scanf( "%f", &cost_per_sq_cm);
    printf( "Enter the number of containers to be manufactured: ");
    scanf( "%d", &quantity);

    //calculations
    surface_area = calc_surface_area(radius, height);

    /*call the calc_cost function here and store the result in the
      cost_per_container variable */

    calc_cost(surface_area, cost_per_sq_cm);
    cost_per_container = calc_cost(surface_area, cost_per_sq_cm);

    total_cost = cost_per_container * quantity;

    //display results
    printf("\nResults:\n\n");
    display_results(radius, height, cost_per_sq_cm, quantity,
                    surface_area, cost_per_container, total_cost);

    return 0;
}

/*******************************************************************
This function calculates the surface area of an open-top cylinder
given the radius of the base and the height of the cylinder

 Input parameters:  radius of the base; must be greater than 0.
 height of the cylinder; must be greater than 0  Return:
 surface area of the open-top cylinder
 ********************************************************************/

float calc_surface_area( float radius, float height)
{
    /* fill in the code for this function */

    return (2 * PI * radius * height) + (PI * pow(radius,2));
}


/*******************************************************************
This function calculates the cost of one open-top container
given the surface area and the cost per square centimeter.

 Input parameters: surface area of the containers; must be greater than 0.
 height of the cylinder; must be greater than 0 Return:
 cost of the cylinders used.

********************************************************************/
float calc_cost( float surface_area, float cost_per_sq_cm)
{
    return surface_area * cost_per_sq_cm;
}


/*******************************************************************
This function displays all items listed in the parameter list.

 Input parameters: radius and height of the cylinder, cost of material,
 quantity to be produced, surface area of the container,
 cost to produce each container, total cost to produce
 the given quantity  Return: none
 ********************************************************************/



void display_results( float radius, float height, float cost_per_sq_cm,
                      int quantity,  float surface_area,
                      float cost_per_container, float total_cost)
{

    /* fill in the code for this function so that the output
    matches that shown in the sample program run */

    printf("Dimensions of container: Radius:%.2f, height:%.2f \n", radius, height);
    printf("Cost of material per square centimeter:%.3f \n", cost_per_sq_cm);
    printf("Quantity desired:%d \n", quantity);
    printf("Surface area of the container:%.3f \n", surface_area);
    printf("Cost per container:%.2f \n", cost_per_container);
    printf("Total cost for the order:%.2f \n", total_cost);


    printf("This Algorithm was designed by Cameron Fox. \n");
}
