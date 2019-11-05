#pragma once

#include <string>
#include <iostream>
#include <iomanip>
//#include <time.h>
//#include <stdlib.h>

#define UNDEFINED_VALUE -1

using namespace std;

template<class T> class MagicBag
{
public:

	// Default Constructor
	MagicBag() {
		item = UNDEFINED_VALUE;
		Bag = nullptr;
		bagSize = 0;
	}

	// Parameterized Constructor
	MagicBag(int newItem) {
		item(newItem);
		Bag = nullptr;
		bagSize = 0;
	}

	// Copy Constructor
	MagicBag(const MagicBag& other) {
		cout << "Copying MagicBag" << endl;

		Bag = other.Bag;
		bagSize = other.bagSize;
		item = other.item;

		Bag = new int[bagSize];
		for (int i = 0; i < bagSize; i++)
		{
			Bag[i] = other.Bag[i];
		}
	}

	MagicBag& operator=(const MagicBag& other) {
		cout << "Deep Copying MagicBag" << endl;

		Bag = other.Bag;
		bagSize = other.bagSize;
		item = other.item;

		if (Bag)
		{
			this->~MagicBag();
		}

		Bag = new int[bagSize];
		for (int i = 0; i < bagSize; i++)
		{
			Bag[i] = other.Bag[i];
		}
		//this->~MagicBag();
		return *this;
	}

	// Operator Overload
	int& operator[](int magicIndex) {

		if (magicIndex >= bagSize)
			throw;
			return Bag[magicIndex];
	}

	// Default Deconstructor
	~MagicBag() {
		delete[] Bag;
	}

	void insert(T item) {
		// Creating a new array for adding a new item into the Magic Bag
		T *newBag = new T[bagSize + 1];

		for (int i = 0; i < bagSize; i++)
		{
			newBag[i] = Bag[i];
		}

		// Adding a new item into the MagicBag
		newBag[bagSize] = item;
		bagSize++;

		// Delete the old Bag in place of the new MagicBag
		this->~MagicBag();
		Bag = newBag;
	}

	T draw() {

		if (bagSize == 0) {
			throw;
		}

		int returnValue;
		srand((unsigned int)time(NULL));
		int randomValue = rand() % bagSize;
		returnValue = Bag[randomValue];
		Bag[randomValue] = Bag[bagSize - 1];
		bagSize--;

		return returnValue;

	}

	int peek(T item) {

		int valueCount = 0;

		for (int i = 0; i < bagSize; i++)
		{
			if (Bag[i] == item)
			{
				valueCount++;
			}

		}

		return valueCount;
	}

	// Member Function: Prints the ostream passed in
	void print(ostream& os)
	{
		os << Bag << endl;
	}

	// Overloaded Print Function
	void print() {
		print(cout);
	}

	friend ostream& operator<<(ostream& os, const MagicBag& mb) {
		for (int i = 0; i < mb.bagSize; i++)
		{
			os << mb.Bag[i] << endl;
		}

		return os;
	}

private:
	// Member Variables
	T *Bag;
	int item;
	int bagSize;
	int magicIndex;
};




