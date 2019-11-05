#ifndef FINALEXAM_H_INCLUDED
#define FINALEXAM_H_INCLUDED
#define NUM_AUTOS 5
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

typedef struct Automobile
{
    int autoID;
    char packageCode;
    float basePrice;
    float finalPrice;
    struct Automobile *next;
}automobile_t;

#endif // FINALEXAM_H_INCLUDED
