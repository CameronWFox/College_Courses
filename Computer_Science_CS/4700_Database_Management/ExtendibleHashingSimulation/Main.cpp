// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once
#include <iostream>
#include "HashTable.h"
#include "Database.h"
#include "Record.h"
#include <string>

using namespace std;

int main()
{
	std::cout << "Hello World!\n";

	/*
	Information on Assignment Below:

	Simulation of Extendible Hashing

	1. The hash value of the hash-key attribute of each record is given as a randomly
		generated integer value.

	2. Each data bucket (block) can store 40 records and is dynamically allocated. Each
		directory entry stores a pointer to a data bucket.

	3. Generate up to 10^4 hash values (to simulate up to 10^4 records), and for every 10^2
		hash values, display followings:

										number of data buckets
	utilization of the directory = ------------------------------------
									number of entries in the directory


														number of total records
	utilization of the data buckets = ----------------------------------------------------------------
										number of records that can be stored in all the data buckets
	*/

	/*
	My Notes on Assignment Below:
	1. 10^4 = 10,000 = total Records = 10,000 total Hash Values.
	2. Each Bucket holds 40 Records: 10,000/40 = 250 total Buckets needed.
	3. I need 10,000 randomly generated integers. (Each randome integer represents a new record).
	4. With Extendible hashing, the Depth of a Bucket is the limit of space.
	5. So the Local Depth is 40 and the Global starts at 40 until it doubles from splitting.
	6. I am not creating 10,000 different records but the randomly generated 10,000 integer values are used
	in place of an actual record and treated as a record itself.

	.CPP Classes Needed For Project:
	1. Main class
	.H Classes Needed For Project:
	1. Bucket class
	2. Directory class or HashTable class (Either one can be used. Both do the same thing).
	3. HashFunction class?
	4. Random Number Generator class (Or just have a random number generator method in the main or one of the
	other classes if needed).

	Stages of the Project Simulation:
	1. Calls the RecordHashValue.h to generate a hash value.
	2. New HashValue is inserted into the Directory.

	*/

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
