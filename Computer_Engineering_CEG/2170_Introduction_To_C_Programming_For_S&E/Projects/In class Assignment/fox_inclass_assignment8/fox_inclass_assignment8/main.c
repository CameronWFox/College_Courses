#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_POINTS 2

typedef struct Point
{
    int x;
    int y;

}point_t;

int main()
{
    point_t point1;
    point_t point2;
    point_t point3;
    point_t point4;

    printf("Please Enter a starting value for the point x: ");
    scanf("%d", &point1.x);

    printf("Please Enter an ending value for the point x: ");
    scanf("%d", &point3.x);

    printf("\nPlease Enter a starting value for the point y: ");
    scanf("%d", &point2.y);

    printf("Please Enter an ending value for the point y: ");
    scanf("%d", &point4.y);

    int distance = sqrt(pow((point1.x - point3.x), 2) + pow((point2.y - point4.y), 2));
    printf("\n\nThe distance between the points is: %d ", distance);
    return 0;
}
