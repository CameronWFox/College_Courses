#pragma once
#include <iostream>
#include "stdafx.h"
#include "HashTable.h"
#include "DataBase.h"
#include "RecordData.h"
#include <string>

using namespace std;

int main()
{
		// Here you build a HashTable variable to test your meythods and make sure the program works correctly
		HashTable<int> first;
		int collisions = 0;
		int value = 0;
		// DataBase Variable
		DataBaseList *myDataBase = new DataBaseList;
		// RecordData Variable
		RecordData *myRecord = new RecordData;
		// the picked choice from the above options
		char studentChoice = ' ';
		// Record Variables given from user
		int keyUID = 0;
		string firstName = " ";
		string lastName = " ";
		string pickedMajor = " ";
		string currentYear = " ";
		// values for searching and deleting
		int studentSearch = 0;
		int studentDelete = 0;
		// user choice to restart the program
		char startAgain = ' ';
		
		do {
		
		// a do-while loop that will rerun if the user enters an incorrect choice out of the following options
		do {
			// Here are the choices for the user to pick an action to interact with the table
			// printed text to give the options out to console
			cout << "Please Pick an Action From The List Below " << endl;
			cout << "[A] Insert a new Student Record" << endl;
			cout << "[B] Delete a Student Record" << endl;
			cout << "[C] Search for a Student Record" << endl;
			cout << "[D] Quit and Exit the program" << endl;
			cout << "Choice: ";
			cin >> studentChoice;
		} while (studentChoice != 'A' && studentChoice != 'B' && studentChoice != 'C' && studentChoice != 'D');

		if (studentChoice == 'A')
		{
			cout << "Please give the infromation to be inserted: " << endl;
			cout << "First Name: ";
			cin >> firstName;
			//cout << endl;
			cout << "Last Name: ";
			cin >> lastName;
			//cout << endl;
			cout << "Student UID: ";
			cin >> keyUID;
			//cout << endl;
			cout << "Student Major(Initials): ";
			cin >> pickedMajor;
			//cout << endl;
			cout << "Student Class Year: ";
			cin >> currentYear;
			//cout << endl;
			system("pause");
			myRecord = myDataBase->studentRecordInsert(keyUID, firstName, lastName, pickedMajor, currentYear);
			first.insert(keyUID, (int)myRecord, collisions);
			
		}
		else if (studentChoice == 'B')
		{
			cout << "Please Enter a UID to search for: ";
			cin >> studentSearch;
			myRecord = myDataBase->studentRecordSearch(studentSearch);
			first.find(studentSearch, (int&)myRecord);
			
		}
		else if (studentChoice == 'C')
		{
			cout << "Please Enter a UID to search for: ";
			cin >> studentDelete;
			myRecord = myDataBase->studentRecordDelete(studentDelete);
			first.remove(studentDelete);
			
		}
		else
		{
			first.alpha();
			system("exit");
		}
		cout << "Want to Run this program?[Y/N]: ";
		cin >> startAgain;

		} while (startAgain == 'Y');
		

	system("pause");
	return 0;
}

