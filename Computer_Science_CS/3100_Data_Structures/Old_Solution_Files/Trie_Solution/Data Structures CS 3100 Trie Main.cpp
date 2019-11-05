#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Trie.h"
#include <vector>
#include <string>
using namespace std;

// function prototype
Trie *readFile();

int main()
{
	//cout << "Please enter a word prefix (Press Enter to exit program): " << endl;
	Trie* fileReader;
	vector<string> resultVector;
	fileReader = readFile();
	fileReader->count();
	fileReader->getSize();
	cout << "Number of words inserted: " << fileReader->count() << endl;
	cout << "Number of nodes in the Trie: " << fileReader->getSize() << endl;
	cout << fileReader->completeCount("cam");
	resultVector = fileReader->complete("addr");
	for (int i = 0; i < resultVector.size(); i++)
	{
		cout << resultVector[i] << " , " << endl;
	}
	system("pause");
	return 0;
}

// This method will read in the file of words
Trie *readFile()
{
	Trie *returnTrie = new Trie();
	ifstream inputFile;
	inputFile.open("wordlist.txt");
	string newWord;
	if (!inputFile.is_open())
	{
		cout << "Cannot open the file!" << endl;
		return returnTrie;
	}
		while (!inputFile.eof())
		{
			getline(inputFile, newWord);
			returnTrie->insert(newWord);
		}
	inputFile.close();
	return returnTrie;
}

