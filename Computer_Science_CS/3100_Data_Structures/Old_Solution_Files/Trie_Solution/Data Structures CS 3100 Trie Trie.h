#pragma once
#include "stdafx.h"
#include <iostream>
#include "TrieNode.h"
#include <string>
#include <vector>

using namespace std;

class Trie
{
private:
	TrieNode *root;
	int wordCount;
	int nodeCount;
public:
	// All my method prototypes
	Trie();
	~Trie();
	bool insert(string);
	int count();
	int getSize();
	bool find(string);
	int completeCount(string);
	int Trie::recursiveCount(TrieNode *, string);
	std::vector <string> complete(string);
	void completeHelp(string, TrieNode *, vector<string>&);
};

