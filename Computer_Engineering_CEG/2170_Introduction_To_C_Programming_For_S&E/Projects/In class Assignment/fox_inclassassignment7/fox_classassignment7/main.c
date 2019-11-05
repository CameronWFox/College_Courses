#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nameSize 100
#define fullNameSize 200

void createFullName(char firstName[], char lastName[], char fullName[]);
int main()
{
    char firstName[nameSize + 1];
    char lastName[nameSize + 1];
    char fullName[fullNameSize + 1];

    printf("Please Enter Your First Name: ");
    gets( firstName);
    printf("Please Enter Your Last Name: ");
    gets( lastName);

    createFullName( firstName, lastName, fullName);
    printf("The Full Name is: %s\n\n", fullName);

    return 0;
}

void createFullName(char firstName[], char lastName[], char fullName[])
{
    strcpy(fullName, "\0");
    strcpy(fullName, firstName);
    strcat(fullName, " ");
    strcat(fullName, lastName);
}
