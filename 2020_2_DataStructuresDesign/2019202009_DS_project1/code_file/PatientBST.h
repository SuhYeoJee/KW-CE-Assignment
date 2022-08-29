#pragma once
#include "PatientBSTNode.h"
#include "PatientNode.h"
#include <fstream>
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

class PatientBST
{
private:
	PatientBSTNode * Root;

public:
	PatientBST();
	~PatientBST();

	PatientBSTNode * GetRoot();
	bool Insert(PatientNode * node);
	bool Search(char * name, PatientBSTNode* node);
	bool Delete(char * name, PatientBSTNode* node);
	void Print_PRE(PatientBSTNode * node);
	void Print_IN(PatientBSTNode * node);
	void Print_POST(PatientBSTNode * node);
	void Print_LEVEL();
	void flogPRINT(PatientBSTNode* node);
};
