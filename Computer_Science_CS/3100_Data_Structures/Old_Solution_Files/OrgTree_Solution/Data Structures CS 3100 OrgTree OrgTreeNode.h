#pragma once
#include <string>
#include <iostream>
#define TREENODEPTR unsigned int
#define TREENULLPTR -1
using namespace std;

class OrgTreeNode
{
private:
	string title;
	string name;
	int parent;
	TREENODEPTR leftmostChild;
	TREENODEPTR rightSibling;
public:
	OrgTreeNode();
	OrgTreeNode(string, string, int, TREENODEPTR, TREENODEPTR);
	//~OrgTreeNode();
	void OrgTreeNode::setTitle(string);
	string OrgTreeNode::getTitle();
	void OrgTreeNode::setName(string);
	string OrgTreeNode::getName();
	void OrgTreeNode::setParent(int);
	int OrgTreeNode::getParent();
	void OrgTreeNode::setLeftMostChild(TREENODEPTR);
	TREENODEPTR OrgTreeNode::getLeftMostChild();
	void OrgTreeNode::setRightSibling(TREENODEPTR);
	TREENODEPTR OrgTreeNode::getRightSibling();
};

