/****************************************************************************************
Author:	            Dave Hutchison
Project (or Lab):	Lab 9
Class:	            CEG 2170
Lecture Section:	N/A
Lab Section:	    N/A
File Name:	        Hutchison_Lab9
Instructor:	        Hutchison
Due Date:	        N/A

Overview:  This program contains several functions that manipulates strings:
1) a function that finds the number of characters in a string
2) a function that shows how many vowels, spaces, etc., are in a string
3) a function that finds the average length string within an array of strings
4) a function that uses parallel arrays of strings
***************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define STR_LEN 51
#define NUM_PEOPLE 24

int findOccurrences( char str[], char ch);
void showCharacterTypes( char str[]);
float findAverageLength( char str[][STR_LEN]);
void formatNames( char firstNames[][STR_LEN], char middleNames[][STR_LEN],
                 char lastNames[][STR_LEN], char formattedNames[][STR_LEN]);
bool readFile( char filename[], char firstNames[][STR_LEN], char middleNames[][STR_LEN],
			   char lastNames[][STR_LEN]);
void printNames( char firstNames[][STR_LEN], char middleNames[][STR_LEN],
			   char lastNames[][STR_LEN], char fullNames[][STR_LEN]);

int main( void) {
    char phrase[STR_LEN];
    char ch;
    int numOccurrences;

    printf( "Enter a word or phrase (no more than %d characters):\n", STR_LEN-1);
    gets( phrase);
    printf( "Enter a character for which to search: ");
    scanf( " %c", &ch);

    numOccurrences = findOccurrences( phrase, ch);
    printf( "\nThe character %c occurs %d times in the phrase.\n\n", ch, numOccurrences);
    showCharacterTypes( phrase);

    char firstNames[NUM_PEOPLE][STR_LEN];
    char middleNames[NUM_PEOPLE][STR_LEN];
    char lastNames[NUM_PEOPLE][STR_LEN];
    char fullNames[NUM_PEOPLE][STR_LEN * 3];
    float averageNameLength;

    if ( readFile( "names.txt", firstNames, middleNames, lastNames)) {
        formatNames( firstNames, middleNames, lastNames, fullNames);
        printNames( firstNames, middleNames, lastNames, fullNames);

        averageNameLength = findAverageLength( fullNames);
        printf( "\n\nThe average name length in the full names array is %.3f.\n\n", averageNameLength);
    } else {
        printf( "Unable to test formatNames and printNames functions.");
    }

    return 0;
}

/**********************************************************************************
This function counts the occurrences of ch within the str.

Input parameters: str - a null-terminated string
                  ch  - the character to search for

Output parameters: none

Return:  the number of times ch occurs within str
**********************************************************************************/
int findOccurrences( char str[], char ch) {
    return 0;
}


/***************************************************************************************
This function displays the number of vowels, the number of digits, the number of
punctuation characters, and the number of whitespace characters within str.

Input parameters: str - a null-terminated string

Output parameters: none

Return:  none
***************************************************************************************/
void showCharacterTypes( char str[]) {

}


/**********************************************************************************
This function finds the average length of the strings contained in the strArray.

Input parameters: strArray - an array of null-terminated strings

Output parameters: none

Return:  the average length of the strings within strArray
**********************************************************************************/
float findAverageLength( char strArray[][STR_LEN]) {
    return 0.0;
}


/**********************************************************************************
This function concatenates the information within the firstNames, middleNames,
and lastNames arrays into one string with the format lastName, firstName, middleName.
This formatted string is stored in the formattedNames array.

Input parameters: firstNames, middleNames, and lastNames arrays. Theses are parallel
arrays (i.e., corresponding positions in each array form a name of a specific
individual), each containing NUM_PEOPLE names.

Output parameters: formattedNames array

Return: none
**********************************************************************************/
void formatNames( char firstNames[][STR_LEN], char middleNames[][STR_LEN],
                 char lastNames[][STR_LEN], char formattedNames[][STR_LEN]) {

}



/**********************************************************************************
This function reads information from the file names.txt into three parallel arrays.

Input parameters:  filename - the name of the file containing the names.  The file
contains names 20 (NUM_PEOPLE) names, one name per line, with spaces between first
name and middle name and last name.	firstNames, middleNames, and lastNames are
arrays to be used in parallel for storing first name, middle name, and last name,
respectively.

Output parameters: firstNames, middleNames, and lastNames arrays.

Return:  none
**********************************************************************************/
bool readFile( char filename[], char firstNames[][STR_LEN], char middleNames[][STR_LEN],
			   char lastNames[][STR_LEN]) {
    FILE *fin;
    int i;
    fin = fopen( filename, "r");
    if ( fin == NULL) {
        printf( "ERROR: Unable to open input file\n");
        return false;
    }
    char name[STR_LEN*3];
	for ( i = 0; i < NUM_PEOPLE; i++) {
	    fgets( name, STR_LEN*3, fin);
	    //remove newline, if read
	    int last_char = strlen( name) - 1;
        if ( name[last_char] == '\n') {
            name[last_char] = '\0';
        }

		sscanf( name,"%s%s%s", firstNames[i], middleNames[i], lastNames[i]);
	}
    return true;
}


/**********************************************************************************
This function prints the names in the parallel arrays in a tabular form.

Input parameters: firstNames, middleNames, lastNames , fullNames arrays. These
are parallel arrays (i.e., corresponding positions in each array form a name of
an individual).

Output parameters: none

Return: none
**********************************************************************************/
void printNames( char firstNames[][STR_LEN], char middleNames[][STR_LEN],
			     char lastNames[][STR_LEN], char fullNames[][STR_LEN]) {
    int i;
	printf( "\nFirst Name      Middle Name     Last Name       Full Name\n\n");
	for ( i = 0; i < NUM_PEOPLE; i++) {
		printf( "%-15s %-15s %-15s %-30s\n", firstNames[i], middleNames[i], lastNames[i],fullNames[i]);
	}
}
