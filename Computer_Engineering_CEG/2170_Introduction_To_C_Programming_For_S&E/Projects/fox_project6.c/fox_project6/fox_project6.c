#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "fox_project6.h"

/*
Author: Cameron Windsor Fox;
Project: 6;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_project6_problem1.c;
Instructor: Hutchison;
Due Date: December 6th, 2016;

Overview: Reads in a text file and then stores it all in a linked list
            then giving the user a set of choices on what to do with the loaded database

Known Issues: None
*/

aircraft_t* readTheAircraft(aircraft_t *head);
aircraft_t *insertNewAircraft(aircraft_t *head, aircraft_t *newAircraft);
void printSingleAircraft(aircraft_t *head);
void printAllAircrafts(aircraft_t *head);
void freeAircraftMemory(aircraft_t *head);
int main()
{
    aircraft_t *head = NULL;
    aircraft_t *newAircraft = (aircraft_t *)calloc( 1, sizeof(aircraft_t));
    char dataBaseChoice = 'z';
    int test = 0;

    do
    {
        // User Database Choice selection
        printf("Aircraft DataBase\n\n");
        printf("L - Load DataBase\n");
        printf("I - Insert New Aircraft\n");
        printf("P - Print Single Aircraft\n");
        printf("A - Print Aircraft DataBase\n");
        printf("X - Exit\n");
        printf("Enter Choice: ");
        scanf("%c", &dataBaseChoice);
        fflush(stdin);

        // User Choice Check Also showing the method calls
        // Checks what method to call based on the user input choice
        switch ( dataBaseChoice)
        {
        case 'l':
        case 'L':
            if (test != 0)
            {
                printf("\n\nError Loading Database!\n\n");
            }
            else
            {
               head = readTheAircraft( head);
                printf("\n\nDatabase Loaded...\n\n");
                test++;
            }
            break;

        case 'i':
        case 'I':
            insertNewAircraft( head, newAircraft);
            break;

        case 'P':
        case 'p':
            printSingleAircraft( head);
            break;

        case 'a':
        case 'A':
            printAllAircrafts( head);
            break;

        case 'x':
        case 'X':
            freeAircraftMemory( head);
            break;
        }

    }
    while (dataBaseChoice != 'x' && dataBaseChoice != 'X');
    return 0;
}


aircraft_t* readTheAircraft(aircraft_t *head)
{
    int i = 0;
    int count = 0;

    FILE *fin = NULL;

    // Opens and reads the text file
    fin = fopen("input.txt", "r");

    if (fin == NULL)
    {
        printf("ERROR OPENING THE FILE!!!!\n");
        exit(0);
    }

    fscanf(fin, "%d", &count);

    // Goes through the Input text file and loads in all the data from the file
    for (i = 0; i < count; i++)
    {
        aircraft_t *current = head;
        aircraft_t *aircraft = (aircraft_t *)calloc( 1, sizeof(aircraft_t));
        aircraft->next=NULL;

        // Reads in each node of the aircraft database
        // Each item that makes up all the data of a single aircraft
        fscanf(fin, "%s", aircraft->name);
        fscanf(fin, "%s", aircraft->nickName);
        fscanf(fin, "%f", &aircraft->wingspan);
        fscanf(fin, "%f", &aircraft->length);
        fscanf(fin, "%f", &aircraft->height);
        fscanf(fin, "%f", &aircraft->weight);
        fscanf(fin, "%f", &aircraft->cost);

        // If the head is empty the data is entered at the head
        if (head == NULL)
        {
            head = aircraft;
        }
        else
        {
            // Finds the end of the list and puts in the new data there
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = aircraft;
        }
    }
    fclose(fin);
    return head;
}

    aircraft_t *insertNewAircraft(aircraft_t *head, aircraft_t *newAircraft)
    {
        aircraft_t *current = head;
        newAircraft = (aircraft_t *)calloc(1, sizeof(aircraft_t));

        // Asks the user for the data require to add a new aircraft to the database
        printf("Please Enter the New Aircraft Name: ");
        scanf("%s", newAircraft->name);
        printf("Please Enter the New Aircraft Nickname: ");
        scanf("%s", newAircraft->nickName);
        printf("Please Enter the New Aircraft Wingspan: ");
        scanf("%f", &newAircraft->wingspan);
        printf("Please Enter the New Aircraft Length: ");
        scanf("%f", &newAircraft->length);
        printf("Please Enter the New Aircraft Height: ");
        scanf("%f", &newAircraft->height);
        printf("Please Enter the New Aircraft Weight: ");
        scanf("%f", &newAircraft->weight);
        printf("Please Enter the New Aircraft Cost: ");
        scanf("%f", &newAircraft->cost);
        fflush(stdin);

        // Checks if the head of the list is empty
        if (head == NULL)
        {
            head = newAircraft;
        }
        else
        {
            // Tests you to go on until you reach the end of the list to add the new node
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newAircraft;
            newAircraft->next = NULL;
        }

        return head;
    }

    void printSingleAircraft(aircraft_t *head)
    {
        aircraft_t *current = head;
        char nameSearch[100];

        // Tests if the list is empty
        if (head == NULL)
        {
            printf("\n\nThe List is Empty!!\n\n");
            return;
        }

        // This will check and see if you name of an aircraft you enter is in the list
        fflush(stdin);
        printf("Please enter the AirCraft Name you want: ");
        gets( nameSearch);

        // Looks for the match aircraft name then prints the data of that single aircraft
        while (current != NULL)
        {
            if (strcmp(current->name, nameSearch) == 0)
            {
                printf("AirCraft Name: %s\n", current->name);
                printf("Aircraft NickName: %s\n", current->nickName);
                printf("AirCraft Wingspan: %f\n", current->wingspan);
                printf("AirCraft Length: %f\n", current->length);
                printf("AirCraft Weight: %f\n", current->weight);

                // tests what to print for the aircraft cost
                if (current->cost == 0.0)
                {
                    printf("AirCraft Cost: CLASSIFIED\n");
                }
                else
                {
                    printf("AirCraft Cost: %f\n", current->cost);
                }
                return;
            }
            current = current->next;
        }
        // If the aircraft name entered is invalid or not found
        printf("Aircraft Not Recognized!! Try Again...\n");
    }

    void printAllAircrafts(aircraft_t *head)
    {
        aircraft_t *current = head;
        if (head == NULL)
        {
            printf("The List is Empty!!");
            return;
        }

        // Loop to print all the data in the database
        while (current != NULL)
        {
            printf("Aircraft Information\n\n");
            printf("AirCraft Name: %s\n", current->name);
            printf("Aircraft NickName: %s\n", current->nickName);
            printf("AirCraft Wingspan: %f\n", current->wingspan);
            printf("AirCraft Length: %f\n", current->length);
            printf("AirCraft Weight: %f\n", current->weight);

            // tests what to print for the aircraft cost
            if (current->cost == 0.0)
            {
                printf("AirCraft Cost: CLASSIFIED\n");
            }
            else
            {
                printf("AirCraft Cost: %f\n", current->cost);
            }
            current = current->next;
        }
    }

    void freeAircraftMemory(aircraft_t *head)
    {
        // Method to free the Memory of the database
        aircraft_t *current = head;

        while (current != NULL)
        {
            aircraft_t *prev = current;
            current = current->next;
            free( prev);
        }
    }

