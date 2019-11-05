#pragma once
#include <iostream>
#include <string>
#include "stdafx.h"

using namespace std;
class RecordData
{
private:
	int studentUID;
	string firstName;
	string lastName;
	string major;
	string classYear;
	RecordData *next;
public:
	friend class DataBaseList;
	RecordData()
	{
		studentUID = 0;
		string firstName = " ";
		string lastName = " ";
		string major = " ";
		string classYear = " ";
		next = NULL;
	}
	~RecordData()
	{

	}
};

