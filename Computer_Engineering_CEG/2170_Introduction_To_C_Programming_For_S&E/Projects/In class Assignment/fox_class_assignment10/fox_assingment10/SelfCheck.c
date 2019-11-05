#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee
{
    int id;
    char name[100];
    float salary;
} employee_t;

void askForInfo(employee_t *ep);
void showsData(employee_t *ep);
int main()
{
    employee_t *ep = NULL;

    ep = (employee_t *)calloc(1, sizeof(employee_t));

    askForInfo( ep);
    showsData( ep);

    free( ep);
    return 0;
}

void askForInfo(employee_t *ep)
{
    printf("Please enter the Employee Name: ");
    gets(ep->name);

    printf("Please enter the Employee ID: ");
    scanf("%d", &ep->id);

    printf("Please enter the Employee Salary: ");
    scanf("%f", &ep->salary);

}

void showsData(employee_t *ep)
{
    printf("\n\nEmployee ID: %d\n", ep->id);
    printf("Employee Name: %s\n", ep->name);
    printf("Employee Salary: %.2f\n\n", ep->salary);
}
