#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CATEGORY "categoryInfo.txt"
#define STORMS "storms.txt"

#define STORMLV 10
#define WINDMIN 10
#define WINDMAX 10
#define STORMID 20
#define WINDPEAK 20

/*
Author: Cameron Windsor Fox;
Project: 5;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_project5_problem1.c;
Instructor: Hutchison;
Due Date: November 15th, 2016;

Overview: Opening two files and checking for wind levels to categorize for Hurricane levels

Known Issues: None
*/

// Method Prototypes
void readCategoryInfo(int Category1[], int Category2[], int Category3[]);
void readStormInfo(int stormID[], int windPeak[]);
void printHeader();
void processStorms(int stormLv[], int windMin[], int windMax[], int stormID[], int windPeak[]);
int main()
{
    int stormLv[STORMLV];
    int windMin[WINDMIN];
    int windMax[WINDMAX];

    int stormID[STORMID];
    int windPeak[WINDPEAK];

    // Methods called
    readCategoryInfo(stormLv, windMin, windMax);
    readStormInfo(stormID, windPeak);
    printHeader();
    processStorms(stormLv, windMin, windMax, stormID, windPeak);
    return 0;
}

void readCategoryInfo(int stormLv[], int windMin[], int windMax[])
{
    // opens the catagoryInfo.txt file
    FILE *fin = NULL;
    int i = 0;
    fin = fopen(CATEGORY, "r");

    for (i = 0; i < 5; i++)
    {
        fscanf(fin, "%d %d %d", &stormLv[i], &windMin[i], &windMax[i]);
        if (fin == NULL)
        {
            printf("ERROR opening the File!!\n\n");
            exit(0);
        }
    }

    fclose(fin);
}

void readStormInfo(int stormID[], int windPeak[])
{
    // opening the storms.txt file
    FILE *fin = NULL;
    int i = 0;
    fin = fopen(STORMS, "r");
    for (i = 0; i < 10; i++)
    {
        fscanf(fin, "%d %d", &stormID[i], &windPeak[i]);
        if (fin == NULL)
        {
            printf("ERROR opening the File!!\n\n");
            exit(0);
        }
    }

    fclose(fin);
}

void printHeader()
{
    // The header for the output
    printf("Storms That Qualify As Hurricanes\n");
    printf("----------------------------------------------------------\n");
    printf("Identification          Peak Wind (mph)           Category\n");
    printf("----------------------------------------------------------\n");
}

void processStorms(int stormLv[], int windMin[], int windMax[], int stormID[], int windPeak[])
{
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        // Statements to check the hurricane levels and wind peaks from the text files
        if (windPeak[i] >= 74 && windPeak[i] <= 95)
        {
            printf("%d %20d %20d\n", stormID[i], windPeak[i], stormLv[0]);
        }
        else if (windPeak[i] >= 96 && windPeak[i] <= 110)
        {
            printf("%d %20d %20d\n", stormID[i], windPeak[i], stormLv[1]);
        }
        else if (windPeak[i] >= 111 && windPeak[i] <= 130)
        {
            printf("%d %20d %20d\n", stormID[i], windPeak[i], stormLv[2]);
        }
        else if (windPeak[i] >= 131 && windPeak[i] <= 155)
        {
            printf("%d %20d %20d\n", stormID[i], windPeak[i], stormLv[3]);
        }
        else if (windPeak[i] >= 156 && windPeak[i] <= 999)
        {
            printf("%d %20d %20d\n", stormID[i], windPeak[i], stormLv[4]);
        }
    }
    // Checks for the Min and the Max wind speed with the corresponding Storm ID
    int j = 0;
    int x = 0;
    int lowest = 100;
    int highest = 0;
    int lowestID = 0;
    int highestID = 0;

    // Checks for the lowest and highest wind peak
    for (j = 0; j < 10; j++)
    {
       if(lowest>windPeak[j])
       {
           lowest = windPeak[j];
       }
       if(highest<windPeak[j])
       {
           highest = windPeak[j];
       }
    }

    // checks for the ID for the the lowest and highest wind peak
    for(x=0;x<10;x++)
    {
        if (windPeak[x] == highest)
        {
            highestID = stormID[x];
        }
        if (windPeak[x] == lowest)
        {
            lowestID = stormID[x];
        }
    }
    printf("\n\nMinimum Wind speed of %d occurred from storm ID %d\n", lowest, lowestID);
    printf("Maximum Wind speed of %d occurred from storm ID %d\n", highest, highestID);
}
