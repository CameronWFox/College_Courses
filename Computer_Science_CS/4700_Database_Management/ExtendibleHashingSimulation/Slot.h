#pragma once

using namespace std;

enum SlotType { normalSlot, emptySlot, tombstoneSlot };

class Slot
{
private:
	int key;
	int hashValue;
	SlotType slotType;
public:

	// EntrySlot Constructor
	Slot()
	{
		key = 0;
		slotType = emptySlot;
	}

	// EntrySlot Parameterized Constructor
	Slot(int newKey, int newHashValue)
		: key(newKey), hashValue(newHashValue)
	{
		slotType = normalSlot;
	}

	// EntrySlot Deconstructor
	~Slot() {}

	void Kill()
	{
		slotType = tombstoneSlot;
	}

	// Returns the current Key
	int getKey() const
	{
		return key;
	}

	// Returns the current HashValue
	unsigned int getHashValue() const
	{
		return hashValue;
	}

	// Check if a record is empty
	bool isEmpty() const {
		return(slotType == emptySlot);
	}

	// Check if a record is a normal record
	bool isNormal() const {
		return(slotType == normalSlot);
	}

	// Check if a record is a tombstone
	bool isTombstone() const {
		return (slotType == tombstoneSlot);
	}
};
