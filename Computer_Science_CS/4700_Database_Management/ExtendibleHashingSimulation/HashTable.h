#pragma once
#include <iostream>
#include "Slot.h"
#define MAXHASH 10,000
using namespace std;

template <int> class HashTable
{
private:
	int global_depth;
	int bucket_size;
public:

	Slot<int> hashArray[MAXHASH];
	int hash_count = 0;

	HashTable()
	{

	}

	~HashTable()
	{

	}

	// You need to insert a new Pair(key/value) into your HashTable
	// Please Return true if the insert is succcessfull
	// Please Return false if the insert fails
	// Duplicate inserted Pairs(key/value) are not allowed
	bool HashTable<T>::insert(int key, T value, int& collisions)
	{

	}

	// You will need to search and find the record with the matching key 
	// then remove it and that will return true for this function
	// If you cannot find the matching key then please return false
	bool HashTable<T>::remove(int key)
	{

	}

	// If you find a record with the matching key please return true 
	// Also a copy of the value in the record is returned in &value
	// If you cant find a matching key please return false
	bool HashTable<T>::find(int key, T& value)
	{

	}

	// Please return the current loading factor a, in the HashTable
	float HashTable<T>::alpha()
	{

	}

	// Your hash table should also overload operator<< such that cout << myHashTable prints all the key/value pairs in the table, 
	// along with their hash table slot, to cout. In order to avoid difficulties that occur when combining templates with 
	// separate .h and .cpp files, you may include your operator<< function definition in your HashTable.h file.
	friend ostream& operator<<(ostream& os, const SlotType& obj)
	{

	}
};
