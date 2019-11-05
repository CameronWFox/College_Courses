#include "stdafx.h"
#include "OrgTreeNode.h"

using namespace std;

OrgTreeNode::OrgTreeNode()
{
	title = " ";
	name = " ";
	parent = 0;
	leftmostChild = TREENULLPTR;
	rightSibling = TREENULLPTR;
}

OrgTreeNode::OrgTreeNode(string title, string name, int parent, TREENODEPTR leftmostChild, TREENODEPTR rightSibling)
{
	this->title = title;
	this->name = name;
	this->parent = parent;
	this->leftmostChild = leftmostChild;
	this->rightSibling = rightSibling;
}

/*
OrgTreeNode::~OrgTreeNode()
{

}
*/

void OrgTreeNode::setTitle(string title)
{
	this->title = title;
}

string OrgTreeNode::getTitle()
{
	return title;
}

void OrgTreeNode::setName(string name)
{
	this->name = name;
}

string OrgTreeNode::getName()
{
	return name;
}

void OrgTreeNode::setParent(int parent)
{
	this->parent = parent;
}

int OrgTreeNode::getParent()
{
	return parent;
}

void OrgTreeNode::setLeftMostChild(TREENODEPTR leftmostChild)
{
	this->leftmostChild = leftmostChild;
}

TREENODEPTR OrgTreeNode::getLeftMostChild()
{
	return leftmostChild;
}

void OrgTreeNode::setRightSibling(TREENODEPTR rightSibling)
{
	this->rightSibling = rightSibling;
}

TREENODEPTR OrgTreeNode::getRightSibling()
{
	return rightSibling;
}
