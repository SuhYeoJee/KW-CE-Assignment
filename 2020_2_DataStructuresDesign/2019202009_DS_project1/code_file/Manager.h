#pragma once
#include "PatientNode.h"
#include "LocationBST.h"
#include "LocationHeap.h"
#include <iostream>
#include <cstdlib> // to use atof(), atoi()
using namespace std;

class Manager
{
private:
	queue <PatientNode *> * ds_queue;
	LocationBST * ds_bst;
	LocationHeap * ds_heap;
	ifstream fin;
	ofstream flog;
	ifstream fdata;

public:
	Manager();
	~Manager();

	void run(char * command);
	bool LOAD(char* cmd); //open "data.txt" & get data
	bool ADD(char* cmd);
	bool QPOP(char* cmd);
	bool SEARCH(char* cmd);
	bool PRINT(char* cmd);
	bool BPOP(char* cmd);

	void PrintErrorCode(int num);
	void PrintSuccess(char * act);
};
