#pragma once
#include <iostream>
#include <stdbool.h>
#include "Slot.h"
#include <string>
#include <iomanip>
#define MAXHASH 1000
using namespace std;

template <class T> class HashTable
{

public:
	Slot<T> hashArray[MAXHASH];
	int hashSize = 0;

	HashTable()
	{
	}

	~HashTable()
	{
	}

	int firstHash(int key)
	{
		return key % MAXHASH;
	}

	int secondHash(int key)
	{
		return (3 - (key % 3));
	}

	// You need to insert a new Pair(key/value) into your HashTable
	// Please Return true if the insert is succcessfull
	// Please Return false if the insert fails
	// Duplicate inserted Pairs(key/value) are not allowed
	bool HashTable<T>::insert(int key, T value, int& collisions)
	{
		int start = firstHash(key);
		int test = start;

		while (hashArray[test].isNormal())
		{
			if (collisions == MAXHASH)
			{
				return false;
			}
			if (hashArray[test].getKey() == key)
			{
				collisions++;
				return false;
			}
			collisions++;
			test = (test + secondHash(key)) % MAXHASH;
		}

		Slot<T> tmp(key, value);
		hashArray[test] = tmp;
		hashSize++;
		cout << "The hashSize is: " << hashSize << endl;
		cout << "The amount of collisions is: " << collisions << endl;
		return true;
	}

	// You will need to search and find the record with the matching key 
	// then remove it and that will return true for this function
	// If you cannot find the matching key then please return false
	bool HashTable<T>::remove(int key)
	{
		int start = firstHash(key);
		int test = start;

		int crash = 0;

		while (hashArray[test].isTombstone() || hashArray[test].isNormal())
		{
			if (crash == MAXHASH)
			{
				crash++;
				return false;
			}
			if (hashArray[test].getKey() == key)
			{
				hashArray[test].kill();
				hashSize--;
				cout << "Key was removed!" << endl;
				return true;
			}
			test = (test + secondHash(key)) % MAXHASH;
			crash++;
		}
		return false;
	}

	// If you find a record with the matching key please return true 
	// Also a copy of the value in the record is returned in &value
	// If you cant find a matching key please return false
	bool HashTable<T>::find(int key, T& value)
	{
		int start = firstHash(key);
		int test = start;
		int crash = 0;

		while (hashArray[test].isTombstone() || hashArray[test].isNormal())
		{
			if (crash == MAXHASH)
			{
				crash++;
				return false;
			}
			if (hashArray[test].getKey() == key)
			{
				value = hashArray[test].getValue();
				cout << "Key was found!" << endl;
				return true;
			}
			test = (test + secondHash(key)) % MAXHASH;
			crash++;
		}
		cout << "Key was not found!" << endl;
		cout << "The number of crashes is: " << crash << endl;
		return false;
	}

	// Please return the current loading factor a, in the HashTable
	float HashTable<T>::alpha()
	{
		float alpha;
		alpha = (float)hashSize / MAXHASH;
		cout << "The alpha is: " << alpha << endl;
		return alpha;
	}

	// Your hash table should also overload operator<< such that cout << myHashTable prints all the key/value pairs in the table, 
	// along with their hash table slot, to cout. In order to avoid difficulties that occur when combining templates with 
	// separate .h and .cpp files, you may include your operator<< function definition in your HashTable.h file.
	friend ostream& operator<<(ostream& os, const SlotType& obj)
	{
		
		for (int i = 0; i < MAXHASH; i++)
		{
			if (obj.isTombstone())
				os << "<<Tombstone>>";
			else if (obj.isEmpty())
				os << "<<Empty>>";

			if (isNormal())
			{
				os << "Slot: " << i << "Key: " << obj.hashArray[i].getKey() << ", Value: " << obj.hashArray[i].getValue();
			}
		}
		return os;
	}
};