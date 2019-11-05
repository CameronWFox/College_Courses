
#include <stdio.h>
#include <conio.h>
#include <math.h>

/*
Author: Cameron Windsor Fox;
Project: 3;
Class: CEG 2170;
Lecture Section: 01;
Lab Section: 05;
File Name: fox_project3_problem1.c;
Instructor: Hutchison;
Due Date: October 11th, 2016;

Overview: This program will be collecting data to display for loan payments and interest rates in organized columns

Known Issues: None
*/

float computeMonthlyPayment(float loanAmount, float annualInterestRate, int loanPerYear);
float computeMonthlyIntrest(float loanAmount, float annualInterestRate);
void printLoanInfo(float loanAmount, float monthlyPayment, float monthlyInterestRate, float annualInterestRate, int loanPerYear, int loanPerMonth);
void printTable(float monthlyPayment, float loanAmount, float annualInterestRate, int loanPerYear);

int main()
{
    float loanAmount = 0.0;
    float interestRate = 0.0;
    int loanPerYear = 0;
    char userChoice = 'z';

    // This do while loop will be used to prompt the user if he or she wants to re-run this program again
    do
    {
        printf("Enter Loan Amount: ");
        scanf("%f", &loanAmount);
        // Checking if the Loan Amount input is valid
        while (loanAmount < 0.0)
        {
            printf("Enter Loan Amount: ");
            scanf("%f", &loanAmount);
        }

        printf("Enter Interest Rate: ");
        scanf("%f", &interestRate);
        // Checking the Yearly Interest Rate input is valid
        while (interestRate < 0.0 || interestRate > 30.0)
        {
            printf("Enter Interest Rate: ");
            scanf("%f", &interestRate);
        }

        printf("Enter Term of Loan (In Years): ");
        scanf("%d", &loanPerYear);
        // Checking the Loan Per Year input is valid
        while (loanPerYear < 0)
        {
            printf("Enter Term of Loan (In Years): ");
            scanf("%d", &loanPerYear);
        }

        // Calculations
        float loanPerMonth = (loanPerYear * 12);
        float annualInterestRate = (interestRate / 100);

        // Methods being called
        float monthlyPayment = computeMonthlyPayment(loanAmount, annualInterestRate, loanPerYear);
        float monthlyInterestRate = computeMonthlyIntrest(loanAmount, annualInterestRate);

        printLoanInfo(loanAmount, monthlyPayment, monthlyInterestRate, annualInterestRate, loanPerYear, loanPerMonth);
        printTable(monthlyPayment, loanAmount, annualInterestRate, loanPerYear);

        // Check if the user wants to re-run the program
        printf("\n Would you like to re-run this program again?: ");
        userChoice = getche();
    }
    while (userChoice == 'y' || userChoice == 'Y');
    return 0;
}

float computeMonthlyPayment(float loanAmount, float annualInterestRate, int loanPerYear)
{
    // Calculates the monthly payment
    float monthlyInterestRate = computeMonthlyIntrest(loanAmount, annualInterestRate);

    return (monthlyInterestRate * loanAmount) / (1 - (pow(1 + monthlyInterestRate, loanPerYear * -12)));
}

float computeMonthlyIntrest(float loanAmount, float annualInterestRate)
{
    // Calculates the monthly interest rate
    float monthlyInterestRate = (annualInterestRate / 12);

    return monthlyInterestRate;
}

void printLoanInfo(float loanAmount, float monthlyPayment, float monthlyInterestRate, float annualInterestRate, int loanPerYear, int loanPerMonth)
{
    // This will be printing out all the basic loan information
    printf("\n LOAN INFORMATION\n\n");
    printf(" Loan Amount: %5.2f\n", loanAmount);
    printf(" Annual Interest Rate: %5.3f%%\n", annualInterestRate * 100);
    printf(" Monthly Interest Rate: %5.3f%%\n", monthlyInterestRate * 100);
    printf(" Loan Per Year: %5d\n", loanPerYear);
    printf(" Loan Per Month: %5d\n", loanPerMonth);
    printf(" Monthly Payment: %5.2f\n", monthlyPayment);
}

void printTable(float monthlyPayment, float loanAmount, float annualInterestRate, int loanPerYear)
{
    int count = 1;
    int month = 0;

    int monthlyLoan = loanPerYear * 12;

    // Titles for each column
    printf("                  Old         Monthly     Interest   Principal       New \n");
    printf("     Month      Balance       Payment       Paid       Paid        Balance \n");
    printf("  ----------  -------------  ----------  ----------  ----------   ---------- \n");

    float principalPayment;
    float newBalance;
    float interestPaid;
    // Loop used to fill in each column of the table
    for (count = 1; count <= monthlyLoan; count++)
    {
        interestPaid = (loanAmount * computeMonthlyIntrest(loanAmount, annualInterestRate));
        principalPayment = monthlyPayment - interestPaid;
        newBalance = loanAmount - principalPayment;
        month++;
        printf("%11d %14.2f %12.2f %11.2f %10.2f %12.2f\n", month, loanAmount, monthlyPayment, interestPaid = loanAmount * (computeMonthlyIntrest(loanAmount, annualInterestRate) / monthlyLoan), principalPayment  = loanAmount - annualInterestRate, newBalance = loanAmount - principalPayment);
        loanAmount = newBalance;
    }
}

