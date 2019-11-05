#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>
#include "finalexam.h"
/*
Author: Cameron Windsor Fox;
Final Exam;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_final_exam_problem1.c;
Instructor: Hutchison;
Due Date: December 12th, 2016;

Overview: CEG 2170 Final Exam

Known Issues: None
*/
automobile_t *insertAuto(automobile_t *head);
void printList(automobile_t *head);
void printAuto(automobile_t *head, int ID);
int main()
{
    automobile_t *head = NULL;
    int autoID = 222;
    int autoID2 = 999;
    int i = 0;
    printList( head);

    for (i = 0; i < NUM_AUTOS; i++)
    {
        insertAuto( head);
    }
    printAuto( head, autoID);
    printAuto( head, autoID2);
    printList( head);
    return 0;
}

automobile_t *insertAuto(automobile_t *head)
{
    automobile_t *current = head;
    automobile_t *newAutomobile = NULL;
    newAutomobile = (automobile_t *)calloc(1,sizeof(automobile_t));
    newAutomobile->next = NULL;
    printf("Please Insert The Following Information:\n\n");
    printf("Enter Auto ID: ");
    scanf("%d", &newAutomobile->autoID);
    printf("Enter package Code(A, B, C): ");
    scanf(" %c", &newAutomobile->packageCode);
    printf("Auto Base Price: ");
    scanf("%f", &newAutomobile->basePrice);

    if (newAutomobile->packageCode == 'a' || newAutomobile->packageCode == 'A')
    {
        newAutomobile->finalPrice = (newAutomobile->basePrice * 0.05);
    }
    else if (newAutomobile->packageCode == 'b' || newAutomobile->packageCode == 'B')
    {
        newAutomobile->finalPrice = (newAutomobile->basePrice * 0.10);
    }
    else if (newAutomobile->packageCode == 'c' || newAutomobile->packageCode == 'C')
    {
        newAutomobile->finalPrice = (newAutomobile->basePrice * 0.15);
    }

    if (head == NULL)
    {
        current = newAutomobile;
    }
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newAutomobile;

    return head;
}

void printList(automobile_t *head)
{
    automobile_t *current = head;
    if (head == NULL)
    {
        printf("The List Is Empty!\n\n");
        return;
    }
    while (current->next != NULL)
    {
        printf("List of Autos: \n\n");
        printf("ID: %d\n", current->autoID);
        printf("Package: %c\n", current->packageCode);
        printf("Base Price: %f\n", current->basePrice);
        printf("Final Price: %f\n", current->finalPrice);
        current = current->next;
    }

}

void printAuto(automobile_t *head, int ID)
{
    automobile_t *current = head;
    printf("AutoID Search: %d",ID);
    if (head == NULL)
    {
        printf("ThOrder of Items on the Stack (The order starts at the Bottom then Ends at the Top)e List Is Empty!");
        return;
    }
    while(current != NULL)
    {
        if (ID == current->autoID)
        {
        printf("List of Autos: \n\n");
        printf("ID: %d\n", current->autoID);
        printf("Package: %c\n", current->packageCode);
        printf("Base Price: %f\n", current->basePrice);
        printf("Final Price: %f\n", current->finalPrice);
        break;
        }
        current = current->next;

    }
    if(current == NULL)
    {
        printf("AUTO NOT FOUND");
    }



}
