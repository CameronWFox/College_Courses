#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "fox_lab10.h"


/*
Author: Cameron Windsor Fox;
Lab: 10;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_lab10_problem1.c;
Instructor: Hutchison;
Due Date: December 2th, 2016;

Overview: This lab will add new values to this list one by one and
            then prints out the list after each new item is added

Known Issues: None
*/

// Prototypes
bool isEmpty( nodeType* pList);
nodeType* addNode( nodeType* pList, int item);
void printList( nodeType* pList);
int countOccurrences( nodeType* pList, int target);
int main(void)
{
    nodeType* list = NULL;
//test isEmpty
    bool empty = isEmpty( list);
    printf( "The list is empty: %s\n", empty ? "true" : "false");
//print an empty list
    printf( "\nThe list contains these items:\n");
    printList( list);
//add a node
    list = addNode( list, 5);
    printf( "\nThe list contains these items:\n");
    printList( list);
//add a node
    list = addNode( list, 1);
    printf( "\nThe list contains these items:\n");
    printList( list);
//add a node
    list = addNode( list, 3);
    printf( "\nThe list contains these items:\n");
    printList( list);
//add a node
    list = addNode( list, 8);
    printf( "\nThe list contains these items:\n");
    printList( list);
//add a node
    list = addNode( list, 5);
    printf( "\nThe list contains these items:\n");
    printList( list);
//test isEmpty
    empty = isEmpty( list);
    printf( "\n\nThe list is empty: %s\n", empty ? "true" : "false");
//test countOccurrences
    int count = countOccurrences( list, 3);
    printf( "The number 3 occurs %d times in the list.\n", count);
    count = countOccurrences( list, 5);
    printf( "The number 5 occurs %d times in the list.\n", count);
    count = countOccurrences( list, 7);
    printf( "The number 20 occurs %d times in the list.\n\n", count);
    return 0;
}
/*********************************************************
* pList is the head of the list
* returns true if list is empty; false if not empty
*********************************************************/
bool isEmpty( nodeType* pList)
{
    // Tests if the List is empty or not
    if (pList == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*******************************************************************
* plist is the head of the list; item is the item to be added
* postcondition: item has been added at the end of the list
*******************************************************************/
nodeType* addNode( nodeType* pList, int item)
{
    nodeType* current = pList;
    nodeType* newNode;

    // Setting the newNode to allocated memory using calloc
    newNode = (nodeType *)calloc( 1, sizeof(nodeType));
    newNode->data = item;
    newNode->next = NULL;

    // Tests if the List has something at the head of the list or not
    if (pList == NULL)
    {
        pList = newNode;
    }
    else
    {
        // Finds the end of the list and adds the next node onto the list
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    return pList;
}
/***********************************************************************
* pList is the head of the list
* postconditon: all items have been printed to the screen on a
* single line no output appears if the list is empty
***********************************************************************/
void printList( nodeType* pList)
{
    nodeType* printNode = pList;

    // Prints out the list
    while (printNode != NULL)
    {
        printf("%d ", printNode->data);
        printNode = printNode->next;
    }

}
/********************************************************************
* pList is the head of the list; target is the item to count
* postconditon: returns number of times target appears in the list
********************************************************************/
int countOccurrences( nodeType* pList, int target)
{
    int count = 0;

    nodeType* nodeCheck = pList;
    while (nodeCheck != NULL)
    {
        if (nodeCheck->data == target)
        {
            count++;
        }
        nodeCheck = nodeCheck->next;
    }
    return count;
}
