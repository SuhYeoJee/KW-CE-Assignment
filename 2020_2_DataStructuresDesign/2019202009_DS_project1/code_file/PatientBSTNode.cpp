#include "PatientBSTNode.h"

PatientBSTNode::PatientBSTNode(PatientNode* node)
{
	pLeft = NULL;
	pRight = NULL;
	Name = node->GetName();
	Disease=((node->GetCough() == 'Y') & (node->GetTemp() >= 37.5)) ? '+' : '-';
}
PatientBSTNode::~PatientBSTNode()
{
	return;
}

char * PatientBSTNode::GetName()
{
	return Name;
}
char PatientBSTNode::GetDisease()
{
	return Disease;
}
PatientBSTNode * PatientBSTNode::GetLeft()
{
	return pLeft;
}
PatientBSTNode * PatientBSTNode::GetRight()
{
	return pRight;
}

void PatientBSTNode::SetName(char * name)
{
	Name = name;
	return;
}
void PatientBSTNode::SetDisease(char disease)
{
	Disease = disease;
	return;
}
void PatientBSTNode::SetLeft(PatientBSTNode * node)
{
	pLeft = node;
	return;
}
void PatientBSTNode::SetRight(PatientBSTNode * node)
{
	pRight = node;
	return;
}
