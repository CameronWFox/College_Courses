#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "OrgTreeNode.h"
#include "OrgTree.h"

using namespace std;

	// Constructor
	OrgTree::OrgTree()
	{
		treeSize = 0;

		title = " ";
		name = " ";

		treeRoot = TREENULLPTR;
	}

	// Deconstructor
	OrgTree::~OrgTree()
	{
		delete[] &treeArray;
	}

	// Creates a root node for the tree
	// If the tree already has a root, the entire tree becomes a subtree of the new root
	void OrgTree::addRoot(string title, string name)
	{
		// Location of the last root added in the tree
		int orgRoot = (treeSize);
		// Adds in a new root to the tree if my array is empty
		if (!treeSize)
		{
			cout << treeRoot << endl;
			treeArray[treeSize].setTitle(title);
			treeArray[treeSize].setName(name);
			treeArray[treeSize].setParent(TREENULLPTR);
			treeArray[treeSize].setLeftMostChild(TREENULLPTR);
			treeArray[treeSize].setRightSibling(TREENULLPTR);
			treeRoot = treeSize;
			treeSize++;
		}
		else
		{
			cout << treeRoot << endl;
			// New root being added into the tree
			treeArray[treeSize].setTitle(title);
			treeArray[treeSize].setName(name);
			treeArray[treeSize].setParent(TREENULLPTR);
			// sets the left child of the new root as the old root
			treeArray[treeSize].setLeftMostChild(treeRoot);
			// right sibling is still null
			treeArray[treeSize].setRightSibling(TREENULLPTR);
			// Setting the old roots parent to the new root
			treeArray[treeRoot].setParent(treeSize);

			treeRoot = treeSize;
			cout << getRoot() << endl;

			// adding 1 to treeSize
			treeSize++;
		}
	}

	// Returns the number of employees in the general tree
	unsigned int OrgTree::getSize()
	{
		return treeSize;
	}

	// Will get the root of the general tree
	TREENODEPTR OrgTree::getRoot()
	{
		return treeRoot;
	}

	// Returns a pointer to the leftmostchild of the node passed in. 
	// Return TREENULLPTR of the node has no chldren
	TREENODEPTR OrgTree::leftMostChild(TREENODEPTR node)
	{
		TREENODEPTR leftmostChild = TREENULLPTR;

		/*
		Checking out of bounds if the node and node + 1 have the same parent.
		This is a faster method of testing than using a loop for the leftmostchild.
		*/
		if(node > 0 && node <= treeSize)
		{
			leftmostChild = treeArray[node].getLeftMostChild();
		}
		return leftmostChild;
	}

	// Returns a pointer to the rightsibling of the node passed in. 
	// Return TREENULLPTR of the node has no right sibling
	TREENODEPTR OrgTree::rightSibling(TREENODEPTR node)
	{
		TREENODEPTR rightsibling = TREENULLPTR;

		// Checking out of bounds if the node and node + 1 have the same parent.
		if (node > 0 && node <= treeSize)
		{
			rightsibling = treeArray[node].getRightSibling();
		}
		return rightsibling;
	}

	// printSubTree method is used to print out the selected subroot of the tree in any section of the tree
	void OrgTree::printSubTree(TREENODEPTR subTreeRoot)
	{
		print(subTreeRoot, 0);
	}

	// printSubTree method is used to print out the selected subroot of the tree in any section of the tree
	void OrgTree::print(TREENODEPTR subTreeRoot, int treeLevel)
	{
		TREENODEPTR leftmostChild = leftMostChild(subTreeRoot);
		TREENODEPTR rightsibling = rightSibling(subTreeRoot);
		if (subTreeRoot != TREENULLPTR)
		{
			cout << treeArray[subTreeRoot].getTitle() << ": " << ", " << treeArray[subTreeRoot].getName() << ": " << endl;

			if (leftmostChild != TREENULLPTR)
			{
				spacing(treeLevel+1);
				print(leftmostChild, treeLevel+1);
			}

			if (rightsibling != TREENULLPTR)
			{
				spacing(treeLevel);
				print(rightsibling, treeLevel);
			}
		}
	}

	// This methiod is used to help with spacing and with indentation for printing the subTreeRoot
	void OrgTree::spacing(int treeLevel)
	{
		for (int i = 0; i < treeLevel; i++)
		{
			cout << "   ";
		}
	}

	// The find method is used for searching for a selected title that the user wants to find a specific emplyee in the tree
	TREENODEPTR OrgTree::find(string title)
	{
		for (int i = 0; i < treeSize; i++)
		{
			if (treeArray[i].getTitle() == title)
			{
				return i;
			}
		}
		return TREENULLPTR;
	}

	// This is the read method
	bool OrgTree::read(string filename)
	{
		TREENODEPTR newEmplyor;
		string newTitle, newName;
		ifstream inFile(filename);

		if (!inFile.is_open()) {
			cerr << "Couldn't open file!" << endl;
			system("cd");
			return false;
		}
		else {
			inFile.open("inputFile.txt");
			if (inFile.peek() == ')')
			{
				return nullptr;
			}
				
					// reads the new title and new name from the file
					getline(inFile, newTitle, ',');
					getline(inFile, newName);
					if (treeRoot = TREENULLPTR)
					{
						addRoot(newTitle, newName);
					}
					else
					{
						hire(newEmplyor, newTitle, newName);
					}
					
					// when you havnt read the ) symbol call the hire function and add this employee to the tree
					if (inFile.peek() == ')')
					{
						hire(leftMostChild(newEmplyor), newTitle, newName);
					}
					if (inFile.peek() == ')' && ')')
					{
						hire(rightSibling(newEmplyor), newTitle, newName);
					}
				
		}
		return true;
	}

	// This is the write method called from main
	void OrgTree::write(string filename)
	{
		int treeDepth = 0;
		TREENODEPTR emplyeerAdded;
		string newTitle, newName;
		ofstream outFile;
		outFile.open(filename);
		if (!outFile.is_open()) {
			cerr << "Couldn't open file!" << endl;
		}

		//if root is not a TREENULLPTR, call writeNodeToFile to begin the recursive calls
		if (treeRoot != TREENULLPTR)
			writeNodeToFile(treeRoot, outFile);

		outFile.close();

	}
	// This is the write method that is called recursively 
	void OrgTree::writeNodeToFile(TREENODEPTR node, ofstream& fileout)
	{
		char treeEnd = ')';
		//prints node out
		fileout << treeArray[node].getTitle() << ", " << treeArray[treeRoot].getName() << endl;
		//check to see if node has a left most child, if yes, go to that node
		if (treeArray[node].getLeftMostChild() != TREENULLPTR)
			writeNodeToFile(treeArray[node].getLeftMostChild(), fileout);
		//if the node no longer has a left child, call its rightsibling 
		if (treeArray[node].getRightSibling() != TREENULLPTR)
			writeNodeToFile(treeArray[node].getRightSibling(), fileout);
		//if there are no more siblings, add a tree end character
		if (treeArray[node].getRightSibling() == TREENULLPTR)
			fileout << treeEnd << endl;
	}


	// This method is used for adding in a new employee into the General Tree
	void OrgTree::hire(TREENODEPTR node, string newTitle, string newName)
	{
		TREENODEPTR tmp;

		//TREENODEPTR leftNode = leftMostChild(node);
		//TREENODEPTR rightNode = rightSibling(node);
		treeSize++;
		// if the leftmost child is null then the new employee will be added in as a left most child.
		if (treeArray[node].getLeftMostChild() == TREENULLPTR)
		{
			treeArray[node].setLeftMostChild(treeSize);
			treeArray[treeSize].setTitle(newTitle);
			treeArray[treeSize].setName(newName);
			treeArray[treeSize].setParent(node);
			return;
		}
		
		// If there is a left most child then I check the right sibling.
		// if there is no right sibling then that is where the new employee will be placed in. 
		tmp = treeArray[node].getLeftMostChild();
		while (treeArray[tmp].getRightSibling() != TREENULLPTR)
		{
			tmp = treeArray[tmp].getRightSibling();

		}
				treeArray[tmp].setRightSibling(treeSize);
				treeArray[treeSize].setTitle(newTitle);
				treeArray[treeSize].setName(newName);
				treeArray[treeSize].setParent(node);
				return;
		
	}

	// This is the fire method that removes am employee from the array then sets the children connected 
	//to the next higher up in the array.
	bool OrgTree::fire(string formerTitle)
	{
		for (int i = 0; i < treeSize; i++)
		{
			// Will not allow the root of the tree to be fired
			if (formerTitle == treeArray[treeRoot].getTitle())
			{
				return false;
			}

			// Checking the tree for the matching title of employee to fire
			while (treeArray[i].getRightSibling() != TREENULLPTR)
			{
				treeArray[treeArray[i].getRightSibling()].setParent(treeArray[i].getParent());
				if (treeArray[i].getTitle() == formerTitle)
				{
					treeArray[treeArray[i].getParent()].setLeftMostChild(treeArray[i].getLeftMostChild());
				}
			}
		}
		return true;
	}

