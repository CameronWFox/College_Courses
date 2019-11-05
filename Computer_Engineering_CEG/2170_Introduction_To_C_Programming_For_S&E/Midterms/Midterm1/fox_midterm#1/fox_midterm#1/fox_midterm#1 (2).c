#include <stdio.h>
#define PRICES 5

/*
Author: Cameron Windsor Fox;
Midterm: 1;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_midterm#1_problem1.c;
Instructor: Hutchison;
Due Date: October 5th, 2016;

Overview: This is our first of two midterm Exams.
          The project deals with multiple functions,
          calling methods and using calculations from input given by the user

Known Issues: None
*/

// Method prototypes
float getPrices();
float computeShipping(int shippingZone);
void printResults(int productID, float averagePrice, float shippingCost);
int main()
{
    int productID;
    int shippingZone;

    // Asking user for input
    printf(" Please enter the Product ID: ");
    scanf("%d", &productID);

    float averagePrice = getPrices();

    printf(" Please enter the Shipping Zone Number(Between 1 and 3): ");
    scanf("%d", &shippingZone);

    // Methods to be called
    float shippingCost = computeShipping(shippingZone);
    printResults(productID, averagePrice, shippingCost);
    return 0;
}

float getPrices()
{
    int count = 0;
    float price = 0.0;
    float priceSum = 0.0;

    // For Loop Testing and gathering five prices from the user
    for (count = 0; count < PRICES; count++)
    {
        printf(" Please enter in a price of your choice: ");
        scanf("%f", &price);
        priceSum = (priceSum + price);
    }
    // Average Price gathered from the user input
    float averagePrice = (priceSum / PRICES);
    return averagePrice;
}

float computeShipping(int shippingZone)
{
    float shippingCost = 0.0;

    // if else if statements to check which shipping zone will be used
    if (shippingZone == 1)
    {
        shippingCost = 00.00;
    }
    else if (shippingZone == 2)
    {
        shippingCost = 10.00;
    }
    else if (shippingZone == 3)
    {
        shippingCost = 20.00;
    }

    return shippingCost;
}

void printResults(int productID, float averagePrice, float shippingCost)
{
    // Display's the output data
    printf(" The Product ID is: %d \n", productID);
    printf(" The Average Price is: $%.2f \n", averagePrice);

    // Checking if there is a shipping cost or if there is no charge at all
    if (shippingCost == 10.00 || shippingCost == 20.00)
    {
        printf(" The Shipping Cost is: $%.2f ", shippingCost);
    }
    else
    {
        printf(" The Shipping Cost is: No charge ");
    }

}
