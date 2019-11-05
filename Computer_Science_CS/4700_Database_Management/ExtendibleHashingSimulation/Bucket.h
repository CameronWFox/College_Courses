#pragma once
#include <iostream>

using namespace std;

class Bucket
{
private:
	int bucket_current_depth;
	int bucket_local_depth;
	int bucket_global_depth;

	int bucket_size;
public:

	Bucket()
	{
		bucket_current_depth = 0;
		bucket_local_depth = 0;
		bucket_global_depth = 0;
		bucket_size = 0;
	}

	~Bucket()
	{

	}
};
