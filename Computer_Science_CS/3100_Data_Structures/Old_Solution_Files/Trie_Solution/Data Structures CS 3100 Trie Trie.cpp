// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Trie.h"

using namespace std;

Trie::Trie()
{
	root = new TrieNode;
	wordCount = 0;
	nodeCount = 0;
}

Trie::~Trie()
{
}

// Inserts a new word into the tree, no duplicates are allowed
// return true is inserted success
// return false if word isn't inserted correctly
bool Trie::insert(string word)
{
	// current node 
	TrieNode *currentNode = root;
	// Checking for duplicates
	int oldNodeCount = nodeCount;
	// index in the array
	int arrayIndex = 0;
	// letter of the word being inserted
	char currentChar = '$';

	// goes thorugh each letter of the word
	for (unsigned int i = 0; i < word.length(); i++)
	{
		// getting the first char from the word being inserted
		currentChar = word[i];
		// finding the entry number in the trieArray to go to for inserting the next letter of the word
		arrayIndex = (currentChar - 'a');
		// moves from node to node if the index doesn't equal NULL
		if (currentNode->trieArray[arrayIndex])
		{
			currentNode = currentNode->trieArray[arrayIndex];
		}
		else {
			// if the current node is NULL a new one is made
			currentNode->trieArray[arrayIndex] = new TrieNode;
			currentNode = currentNode->trieArray[arrayIndex];
			// adding a new node to the trie
			nodeCount++;
		}
	}
	// Insert the '$' pointer
	arrayIndex = ARRAY_SIZE - 1;
	// setting the new node with the current letter of the word being inserted
	if (currentNode->trieArray[arrayIndex])
	{
		currentNode = currentNode->trieArray[arrayIndex];
	}
	else {
		currentNode->trieArray[arrayIndex] = new TrieNode;
		currentNode = currentNode->trieArray[arrayIndex];
		// adding a new node to the trie
		nodeCount++;
	}
	// Checks for duplicate inserting
	if (oldNodeCount == nodeCount)
	{
		cout << "This is a duplicate, please insert a different string!" << endl;
		return false;
	}
	wordCount++;
	return true;
}

// return number of words in the trie
int Trie::count()
{
	return wordCount;
}

// returns the total number of nodes in the trie
int Trie::getSize()
{
	return nodeCount;
}


// return true of the given word is found in the AVL tree
// otherwise return false
bool Trie::find(string wordSearch)
{
	// current node 
	TrieNode *currentNode = root;

	// letter being searched in the trie
	char charSearch = ' ';
	// index for searching for the selected word
	int searchIndex = 0;

	for (unsigned int i = 0; i < wordSearch.length(); i++)
	{
		// getting the first char from the word being searched for
		charSearch = wordSearch[i];
		// finding the entry number in the trieArray to go to for searching the next letter of the word
		searchIndex = (charSearch - 'a');
		// setting the new node with the current letter of the word being searched
		if (currentNode->trieArray[searchIndex])
		{
			currentNode = currentNode->trieArray[searchIndex];
		}
		else {
			cout << "Word Not In Trie! Please Search Again!" << endl;
			return false;
		}
	}
	//if the current node is not null and the current node has a end of word pointer
	return (currentNode && currentNode->trieArray[ARRAY_SIZE - 1]);
}

// return the number of words found with the given input string Prefix
// if none are found, return zero
int Trie::completeCount(string wordPrefix)
{
	// current node
	TrieNode* current = root;

	// char currently looking at
	char currentCharacter = ' ';
	char endLetter = '$';
	// number of words containig the prefix
	int total = 0;

	int currentIndex = 0;

	for (unsigned int i = 0; i < wordPrefix.length(); i++)
	{
		currentCharacter = wordPrefix[i];
		currentIndex = (currentCharacter - 'a');
		// setting the current node with the current letter of the prefix being tested for
		if (current->trieArray[currentIndex])
		{
			current = current->trieArray[currentIndex];
		}
	}

	//// travel the array for the index pointing to node and not null
	total = recursiveCount(current, wordPrefix);

	return total;
}

int Trie::recursiveCount(TrieNode *nodeLetter, string word)
{
	int count = 0;
	if (nodeLetter && nodeLetter->trieArray[ARRAY_SIZE - 1])
	{
		count++;
	}
		
	for (int i = 0; i < ARRAY_SIZE - 1; i++)
	{
		if (nodeLetter->trieArray[i])
		{
			count += recursiveCount(nodeLetter->trieArray[i], word + char('a' + i));
		}
	}

	return count;
}

// return a C++ vector of strings containing all the words in the dictionary
// beginning with the given input string Prefix
// if no words are found return an empty vector
std::vector<string> Trie::complete(string vectorPrefix)
{
	TrieNode* current = root;
	vector<string> results;

	char character;

	for (unsigned int i = 0; i < vectorPrefix.length(); i++)
	{
		character = vectorPrefix[i];
		//current = current->trieArray[i];
	}
	// calling my completeHelp method
	completeHelp(vectorPrefix, current, results);
	
	return results;
}

// This is my complete help method that will find each word that contains the 
void Trie::completeHelp(string vectorPrefix,TrieNode* current, vector<string> &results)
{
	if (current->trieArray[ARRAY_SIZE - 1])
	{
		results.push_back(vectorPrefix);
	}
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (current->trieArray[i])
		{
			char addPrefix = (i + 'a');
			completeHelp(vectorPrefix + addPrefix, current->trieArray[i], results);
		}
	}
	
}

