#pragma once
#include <iostream>
#include <string>
#include "Record.h"

using namespace std;

class Database
{
private:
	//DataBase Variables
	Record* database_head;
	Record* database_tail;
	int entry_count;
public:

	// Database Constructor
	Database()
	{
		database_head = NULL;
		database_tail = NULL;
		entry_count = 0;
	}

	// Database Deconstructor
	~Database()
	{

	}

	// inserts a new record
	Record* insert()
	{

	}

	// Removes a specific record
	Record* remove()
	{

	}

	// Searches for a specific record
	Record* search()
	{

	}
};
