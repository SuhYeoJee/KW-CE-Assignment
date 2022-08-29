#include "PatientNode.h"

PatientNode::PatientNode()
{
	Name = NULL;
	Temperature = 0;
	Cough = NULL;
	Location = NULL;
}
PatientNode::~PatientNode()
{
	if (Name) delete[] Name;
	if (Location) delete[] Location;
	return;
}

char * PatientNode::GetName()
{
	return Name;
}
float PatientNode::GetTemp()
{
	return Temperature;
}
char PatientNode::GetCough()
{
	return Cough;
}
char * PatientNode::GetLoc()
{
	return Location;
}

void PatientNode::SetName(char * name)
{
	Name = new char[10];
	strcpy(Name, name);
	return;
}
void PatientNode::SetTemp(float temp)
{
	Temperature = temp;
	return;
}
void PatientNode::SetCough(char cough)
{
	Cough = cough;
	return;
}
void PatientNode::SetLoc(char * location)
{
	Location = new char[20];
	strcpy(Location, location);
	return;
}