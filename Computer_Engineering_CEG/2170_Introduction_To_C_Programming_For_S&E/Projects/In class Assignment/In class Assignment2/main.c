#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float computeArea(float radius);
int main()
{
    printf("Hello world!\n");

    float radius;
    printf("Please enter a radius for a circle of your choice: ");
    scanf("%f", &radius);

    computeArea(radius);
    return 0;
}

float computeArea (float radius)
{
    float area;

    // The calculation used
    area = (M_PI * pow(radius, 2));

    // Printing out the results with two decimal places
    printf("The area of the circle with radius: %f is: %f \n\n", radius, area);

    return 0.0;

}
