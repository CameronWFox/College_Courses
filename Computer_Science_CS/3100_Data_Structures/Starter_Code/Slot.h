#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

// There are three types of slots in a closed hash:
// Normal slots, empty slots, and tombstones
enum SlotType {normalSlot, emptySlot, tombstone};


// Each slot holds an integer key and an integer value.
// The integer value will be used as an index into the
// record store.

class Slot
{
private:
	int key;
	int value;
	SlotType type;

public:

	// The default constructor produces an empty slot.
	Slot()
	{
		key = 0;
		type = emptySlot;
	}

	// This constructor uses an initialization list
	// See "member initialization" at: https://urldefense.proofpoint.com/v2/url?u=http-3A__www.cplusplus.com_doc_tutorial_classes_&d=DwIGAg&c=3buyMx9JlH1z22L_G5pM28wz_Ru6WjhVHwo-vpeS0Gk&r=cqARsoQS3FvRkcVh2tPwyd3_tAwqELs9_YxtM0adVHQ&m=FyJVITd8PIwVnLvW2djv6GgpESBRlAI2xffU02NSRJg&s=6E0t775Tqfe2VXvWVDAP2ybYedp-VLgs7g4tUSGeyU8&e=
	Slot(int newkey, int newvalue)
		: key(newkey), value(newvalue)
	{
		type = normalSlot;
	}

	// Convert a slot to a tombstone
	void kill() {
		type = tombstone;
	}

	// Get the integer key of a slot
	int getKey() const {
		return key;
	}

	// Get the value of a slot
	int getValue() const {
		return value;
	}

	// Check if a slot is empty
	bool isEmpty() const {
		return(type == emptySlot);
	}

	// Check if a slot is a normal slot
	bool isNormal() const {
		return(type == normalSlot);
	}

	// Check if a slot is a tombstone
	bool isTombstone() const {
		return (type == tombstone);
	}

	// Overload the << operator for printing slots
	friend ostream& operator<<(ostream& os, const Slot& me) {
		if (me.isTombstone())
			os << "<<Tombstone>>";
		else if (me.isEmpty())
			os << "<<Empty>>";
		else
			os << "Key: " << me.key << ", Value: " << me.value;
		return os;
	}

	// No destructor is needed as Slots don't use any dynamically
	// allocated memory
	~Slot()
	{
	}
};

