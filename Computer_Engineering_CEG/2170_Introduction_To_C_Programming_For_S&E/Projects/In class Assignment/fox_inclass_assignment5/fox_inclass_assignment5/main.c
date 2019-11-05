#include <stdio.h>
#include <stdlib.h>

void getGrade(float grade, char *letterGrade);
int main()
{
    float grade = 0.0;
    char letterGrade= 'Z';
    printf( "Enter number grade: ");
    scanf( "%f", &grade);
    getGrade( grade, &letterGrade);
    printf( "Final numeric grade: %.2f\n", grade);
    printf( "Final letter grade:  %c\n", letterGrade);
    return 0;
}

void getGrade(float grade, char *letterGrade)
{
    grade = grade + 0.5;
    if (grade <= 100.0 && grade >= 90.0)
    {
        *letterGrade = 'A';

    }
    else if (grade <= 89.0 && grade >= 80.0)
    {
        *letterGrade = 'B';

    }
    else if (grade <= 79.0 && grade >= 70.0)
    {
        *letterGrade = 'C';

    }
    else if (grade <= 69.0 && grade >= 60.0)
    {
        *letterGrade = 'D';

    }
    else if (grade <= 59.0 && grade >= 00.0)
    {
        *letterGrade = 'F';

    }
}
