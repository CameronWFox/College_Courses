#pragma once
#include <iostream>
#include <string>
#include "stdafx.h"
#include "RecordData.h"

using namespace std;
class DataBaseList
{
private:
	// Link List variables
	RecordData *baseHead;
	RecordData *baseTail;
	int count;
public:
	DataBaseList()
	{
		// Link List variables
		baseHead = NULL;
		baseTail = NULL;
		count = 0;
	}

	~DataBaseList()
	{
		RecordData *killTarget;
		RecordData *killNextTarget;

		if (baseHead)
		{
			killTarget = baseHead;
			killNextTarget = baseHead->next;

			delete(killTarget);
			while (killNextTarget)
			{
				killTarget = killNextTarget;
				killNextTarget = killNextTarget->next;
				delete(killTarget);
			}
		}

	}

	// inserts a new record with a studentUID, firstName, lastName, major, and classYear
	RecordData* studentRecordInsert(int UID, string fName, string lName, string studentMajor, string year)
	{
		int oldCount = count;
		// Adding a new Node to the Link List DataBase
		RecordData *newNode = new RecordData;
		for (int i = 0; i < count; i++)
		{

		}
			if (baseHead == NULL)
			{
				count++;
				baseHead = newNode;
				newNode->firstName = fName;
				newNode->lastName = lName;
				newNode->studentUID = UID;
				newNode->major = studentMajor;
				newNode->classYear = year;
			}
			else
			{
				baseHead = baseHead->next;
			}
			if (count == oldCount)
			{
				cout << "This Record is already inserted into the DataBase." << endl;
				return newNode;
			}
			cout << "Inserting a new Record." << endl;
			cout << "First Name: " << newNode->firstName << endl;
			cout << "Last Name: " << newNode->lastName << endl;
			cout << "Student UID: " << newNode->studentUID << endl;
			cout << "Student Major: " << newNode->major << endl;
			cout << "Student Class Year: " << newNode->classYear << endl;
			cout << "Record Inserted." << endl;
			return newNode;
	}
	// Searches for a record in the list by the UID
	RecordData* studentRecordSearch(int UID)
	{
		RecordData *searchingNode = new RecordData;
		searchingNode = baseHead;

		for (int i = 0; i < count; i++)
		{
			if (searchingNode->studentUID == UID)
			{
				cout << "Searching... Record Found." << endl;
				cout << "First Name: " << searchingNode->firstName << endl;
				cout << "Last Name: " << searchingNode->lastName << endl;
				cout << "Student UID: " << searchingNode->studentUID << endl;
				cout << "Student Major: " << searchingNode->major << endl;
				cout << "Student Class Year: " << searchingNode->classYear << endl;
				return searchingNode;
			}
			searchingNode = searchingNode->next;
		}

		cout << "Record not Found." << endl;
		
		return searchingNode;
	}
	// Removes a record from the List be the UID
	RecordData* studentRecordDelete(int UID)
	{
		RecordData *deleteNode = new RecordData;
		RecordData *prevNode = new RecordData;
		deleteNode = baseHead;
		cout << "Searching... ";
		
		for (int i = 0; i < count; i++)
		{
			if (deleteNode->studentUID == UID)
			{
				prevNode->next = deleteNode->next;
				cout << "Record Deleted." << endl;
				
				return deleteNode;
			}
			prevNode = deleteNode;
			deleteNode = baseHead->next;
		}
		cout << "Record not Found." << endl;

		return deleteNode;
	}
};

