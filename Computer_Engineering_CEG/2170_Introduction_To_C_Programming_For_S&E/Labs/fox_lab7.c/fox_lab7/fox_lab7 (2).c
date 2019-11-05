#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 20
#define SPEECH "speech.txt"


/*
Author: Cameron Windsor Fox;
Lab: 7;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab7_problem1.c;
Instructor: Hutchison;
Due Date: October 28th, 2016;

Overview: This program reads from a file and calculates the mean, variance, standard deviation, and the power and magnitude

Known Issues: None
*/

int readSpeechTimes(float arraySpeech[]);
void printSpeechTimes(float arraySpeech[], int sum);
float computeMean(float arraySpeech[], int sum);
float computeVariance(float arraySpeech[], int sum, float speechAverage);
float computeStandardDeviation(float variance);
float computePower(float arraySpeech[], int sum);
float computeMagnitude(float arraySpeech[], int sum);
int main()
{
float arraySpeech[SIZE] = { 0 };

// Methods Called
int sum = readSpeechTimes(arraySpeech);
// Prints how many values are in the array
printf("Number of values in the Array: %d\n\n", sum);
printSpeechTimes(arraySpeech, sum);

// Methods are only called if the if statement is true and printing out data
if (sum > 0)
{
float speechAverage = computeMean(arraySpeech, sum);
printf("\n\nMean: %20.2f", speechAverage);
float variance = computeVariance(arraySpeech, sum, speechAverage);
printf("\nVariance: %18.3f", variance);
float standardDeviation = computeStandardDeviation(variance);
printf("\nStandard Deviation: %7.3f", standardDeviation);
float power = computePower(arraySpeech, sum);
printf("\nPower: %21.3f", power);
float magnitude = computeMagnitude(arraySpeech, sum);
printf("\nMagnitude: %14.1f", magnitude);
}


    return 0;
}

int readSpeechTimes(float arraySpeech[])
{
    FILE *fin = NULL;
    int sum = 0;
    // Opens the file and reads it
    fin = fopen(SPEECH, "r");

    // Error checks if there is a problem opening the file
    if (fin == NULL)
    {
        printf("Error Opening The File!");
        exit(0);
    }
    // reading in the values and storing them into the array
    for (sum = 0; sum < SIZE; sum++)
    {
        fscanf(fin, "%f", &arraySpeech[sum]);
        // Breaks from printing if fscanf encounters a zero
        if (feof(fin))
        {
            break;
        }
    }
    fclose(fin);
    return sum;
}

void printSpeechTimes(float arraySpeech[], int sum)
{
    int i = 0;
    // Loop for finding the number of speech times
    for (i = 0; i < sum; i++)
    {
        // check for when to go to the next line when printing
        if (i == 10)
        {
            printf("\n");
        }
        printf("%5.1f", arraySpeech[i]);
    }
}

float computeMean(float arraySpeech[], int sum)
{
    int i = 0;
    float speechSum = 0.0;
    // Loop for computing the Mean
    for (i = 0; i < SIZE; i++)
    {
        // Calculates the speechSum
        speechSum += (arraySpeech[i] / sum);
    }
    return (speechSum);
}

float computeVariance(float arraySpeech[], int sum, float speechAverage)
{
    int i = 0;
    float variance = 0.0;
    float sumVariance =0;
    // Loop for computing the Variance
    for (i = 0; i < sum; i++)
    {
        // Calculates the sumVariance
        sumVariance += pow((arraySpeech[i] - speechAverage), 2);
    }
    // Setting the variance
    variance = (sumVariance / (sum - 1));
    return (variance);
}

float computeStandardDeviation(float variance)
{
    return sqrt(variance);
}

float computePower(float arraySpeech[], int sum)
{
    int i = 0;
    float power = 0.0;
    // Loop for checking to find the power
    for (i = 0; i < sum; i++)
    {
        // Calculates the average power
        power += ((pow(arraySpeech[i], 2)) / sum);
    }

    return power;
}

float computeMagnitude(float arraySpeech[], int sum)
{
    int i = 0;
    float magnitude = 0.0;
    // Loop used to calculate the magnitude
    for (i = 0; i < sum; i++)
    {
        // Calculates the average magnitude
        magnitude += (fabs(arraySpeech[i]) / sum);
    }
    return magnitude;
}




