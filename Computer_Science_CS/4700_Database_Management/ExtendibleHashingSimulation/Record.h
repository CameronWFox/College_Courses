#pragma once
#include <iostream>

using namespace std;

class Record
{
private:
	int current_hash_value;
	int total_hash_values;
	Record* next_hash_value;
public:

	Record()
	{
		current_hash_value = 0;
		total_hash_values = 10, 000;
		next_hash_value = NULL;
	}

	~Record() {}

	unsigned int GenerateNewHashValue()
	{
		unsigned int newHashValue = 0;
	}
};
