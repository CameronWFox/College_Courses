#ifndef FOX_PROJECT6_H_INCLUDED
#define FOX_PROJECT6_H_INCLUDED
#define NAME 10
#define NICKNAME 20
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

typedef struct Aircraft
{
    char name[NAME];
    char nickName[NICKNAME];
    float wingspan;
    float length;
    float height;
    float weight;
    float cost;
    struct Aircraft *next;
} aircraft_t;

#endif // FOX_PROJECT6_H_INCLUDED
