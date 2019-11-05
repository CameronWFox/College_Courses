#pragma once
#include <iostream>
#include <stdbool.h>
#include <string>
#include "OrgTreeNode.h"

#define TREENODEPTR unsigned int
#define TREENULLPTR -1

using namespace std;

class OrgTree
{
private:
	// OrgTree private varialbes
	OrgTreeNode treeArray[24];
	TREENODEPTR treeRoot;
	string title;
	string name;
	int treeSize;

public:
	OrgTree();
	~OrgTree();
	void addRoot(string, string);
	// All my method prototypes
	unsigned int getSize();
	TREENODEPTR getRoot();
	TREENODEPTR leftMostChild(TREENODEPTR);
	TREENODEPTR rightSibling(TREENODEPTR);
	void printSubTree(TREENODEPTR);
	void print(TREENODEPTR, int);
	void spacing(int);
	TREENODEPTR find(string);
	bool read(string);
	void write(string);
	void writeNodeToFile(TREENODEPTR, ofstream&);
	void hire(TREENODEPTR, string, string);
	bool fire(string);

};