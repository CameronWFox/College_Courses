#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#define ARRAY_SIZE 27
using namespace std;

class TrieNode
{
private:
	TrieNode *trieArray[ARRAY_SIZE];
public:
	TrieNode()
	{
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			//index = i;
			trieArray[i] = NULL;
		}
	}

	~TrieNode()
	{
		delete[] &trieArray;
	}
	
	friend class Trie;
};

