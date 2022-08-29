#include "LocationNode.h"

LocationNode::LocationNode()
{
	Location = NULL;
	BST = NULL;
	pLeft = NULL;
	pRight = NULL;
}

LocationNode::~LocationNode()
{
	return;
}

char * LocationNode::GetLoc()
{
	return Location;
}
PatientBST * LocationNode::GetBST()
{
	return BST;
}
LocationNode * LocationNode::GetLeft()
{
	return pLeft;
}
LocationNode * LocationNode::GetRight()
{
	return pRight;
}

void LocationNode::SetLoc(char * location)
{
	Location = location;
	return;
}
void LocationNode::SetPatientBST(PatientBST* bst) {
	BST = bst;
	return;
}
void LocationNode::SetLeft(LocationNode * node)
{
	pLeft = node;
	return;
}
void LocationNode::SetRight(LocationNode * node)
{
	pRight = node;
	return;
}
