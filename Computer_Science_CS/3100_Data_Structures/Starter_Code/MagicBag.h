#pragma once

#include <iostream>

using namespace std;

template<class T> class MagicBag
{
public:

	MagicBag() {
	}
	
	MagicBag(const MagicBag& other) {
	}
	
	MagicBag& operator=(const MagicBag& other) {
	}
	
	~MagicBag() {
	}

	void insert(T item) {
	}

	T draw() {
	}

	int peek(T item) {
	}

private:

	friend ostream& operator<<(ostream& os, const MagicBag& mb) {
	}
};
