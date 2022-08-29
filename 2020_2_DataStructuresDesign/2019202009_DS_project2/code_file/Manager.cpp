#include "Manager.h"

void Manager::run(const char* command) {
	fin.open(command);
	flog.open("log.txt", ios::app);
	if (!fin) { //if no txt file
		ofstream temp;
		temp.open(command,ios::app); //make command.txt
		temp.close();
		fin.open(command); //open command.txt
	}
	while (!fin.eof()) {
		try  {
			fin.getline(cmd, 32); //read command file
			char* tmp = NULL, *para = NULL; // to save function name
			tmp = strtok_r(cmd, " ", &para); //if command has parameter
			if (strlen(cmd) == 0) continue; //empty line

			if (strcmp(tmp, "LOAD") == 0) {
				flog << "======== LOAD ========" << endl;
				if(*para) throw 100; //too many Parameters
				if (LOAD()) printSuccessCode();
				else throw 100;
			}
			else if (strcmp(tmp, "BTLOAD") == 0) {
				flog << "======== BTLOAD ========" << endl;
				if (*para) throw 200; //too many Parameters
				if (BTLOAD()) printSuccessCode();
				else throw 200;
			}
			else if (strcmp(tmp, "PRINT_ITEMLIST") == 0) {
				flog << "======== PRINT_ITEMLIST ========" << endl;
				if (*para) throw 300; //too many Parameters
				if (!PRINT_ITEMLIST())  throw 300;
			}
			else if (strcmp(tmp, "PRINT_FPTREE") == 0) {
				flog << "======== PRINT_FPTREE ========" << endl;
				if (*para) throw 400; //too many Parameters
				if (!PRINT_FPTREE()) throw 400;
			}
			else if (strcmp(tmp, "PRINT_MIN") == 0) {
				flog << "======== PRINT_MIN ========" << endl;
				// get parameters
				if (!(*para)) throw 500; // No Parameters
				char* item, *start;
				if (!(item = strtok_r(para, " ", &para))) throw 500;//no item parameter
				if (!(start = strtok_r(para, " ", &para))) throw 500; //no start parameter
				if (*para) throw 500; // too many Parameters
				if (!PRINT_MIN(item, atoi(start))) throw 500;
			}
			else if (strcmp(tmp, "PRINT_CONFIDENCE") == 0) {
				flog << "======== PRINT_CONFIDENCE ========" << endl;
				// get parameters
				if (!(*para)) throw 600; // No Parameters
				char* item, *rate;
				if (!(item = strtok_r(para, " ", &para))) throw 600;//no item parameter
				if (!(rate = strtok_r(para, " ", &para))) throw 600; //no rate parameter
				if (*para) throw 600; // too many Parameters
				if (!PRINT_CONFIDENCE(item, atof(rate))) throw 600;
			}
			else if (strcmp(tmp, "PRINT_RANGE") == 0) {
				flog << "======== PRINT_RANGE ========" << endl;
				// get parameters
				if (!(*para)) throw 700; // No Parameters
				char* item, *start, *end;
				if (!(item = strtok_r(para, " ", &para))) throw 700;//no item parameter
				if (!(start = strtok_r(para, " ", &para))) throw 700; //no start parameter
				if (!(end = strtok_r(para, " ", &para))) throw 700; //no end parameter
				if (*para) throw 700; // too many Parameters
				if (!PRINT_RANGE(item, atoi(start), atoi(end))) throw 700;
			}
			else if (strcmp(tmp, "SAVE") == 0) {
				flog << "======== SAVE ========" << endl;
				printErrorCode(800);
			}
			else if (strcmp(tmp, "EXIT") == 0) {
				flog << "======== EXIT ========" << endl;
				printSuccessCode();
				break;
			}
			else {
				flog << "===========================" << endl;
				flog << "======== ERROR Command ========" << endl;
				flog << "===========================" << endl << endl;
			}
		}
		catch (int e) { printErrorCode(e); }
	}
	
	fin.close();
	return;
}

bool Manager::LOAD() {
	if (fpgrowth->isExist()) return false; //already exist
	fstream fdata; //"market.txt"
	fdata.open("market.txt"); 
	if (!fdata) { //if no txt file
		throw 100;
	}

	///////////////make HeaderTable///////////////

	char items[255];
	while (!fdata.eof()) {
		fdata.getline(items, 255, '\n'); //read market.txt
		char* item = items, *temp;
		if (strchr(items, '\t')) item = strtok_r(items, "\t", &temp); // item>=2
		else if (strlen(items) == 0) continue; //empty line
		while (item) {
			fpgrowth->getHeaderTable()->insertTable(item, 1);
			item = strtok_r(temp, "\t", &temp);
		}
	}
	fpgrowth->getHeaderTable()->descendingIndexTable();//sort	
	fdata.close();

	///////////////make FPTree///////////////

		///////make item_array///////

	fdata.open("market.txt");
	while (!fdata.eof()) {
		list<string> item_array;
		fdata.getline(items, 255, '\n'); //read market.txt
		char* ctemp = NULL;
		char* item = strtok_r(items, "\t",&ctemp);
		while (item) {
			item_array.push_back((string)item);
			item = strtok_r(ctemp, "\t",&ctemp);
		}

			///////sort///////
		string tempItem;
		list<pair<int, string> > temp;
		list<pair<int, string> > index = fpgrowth->getHeaderTable()->getindexTable();
		list<pair<int, string> >::iterator insertIter, tempIter; //find item
		int i;
		while (!item_array.empty()) {
			tempItem = item_array.front();//item to insert
			for (insertIter = index.begin(); insertIter != index.end(); insertIter++)
				if ((*insertIter).second == tempItem) break;
			if (insertIter == index.end()) return false;
			if (temp.empty()) {
				temp.push_back((*insertIter));
			}
			else {
				for (tempIter = temp.begin(); (*insertIter).first <= (*tempIter).first; tempIter)
					if (++tempIter == temp.end()) break;
				temp.insert(tempIter, (*insertIter)); //insert
			}
			item_array.pop_front();
		}
		// temp is sorted list	// copy to item_array
		tempIter = temp.begin();
		item_array.clear();
		for (tempIter = temp.begin(); tempIter != temp.end(); tempIter++) {
			item_array.push_back((*tempIter).second);
		}

		///////make FPtree path///////
		fpgrowth->createFPtree(fpgrowth->getTree(), fpgrowth->getHeaderTable(), item_array, 1);
	}
	fdata.close();
	return true;
}

bool Manager::BTLOAD() {
	if (bptree->getRoot()) return false; //already exist
	fstream fdata; //"result.txt"
	fdata.open("result.txt"); if (!fdata) throw 200; // No file 

		///////make set///////
	char items[255];
	while (!fdata.eof()) {
		set<string> set;
		fdata.getline(items, 255, '\n'); //read market.txt
		char* temp = NULL;
		char* item = strtok_r(items, "\t", &temp); if (!item) continue;
		int key = atoi(item);
		item = strtok_r(temp, "\t",&temp);
		while (item) {
			set.insert((string)item);
			item = strtok_r(temp, "\t", &temp);
		}
		bptree->Insert(key, set);
	}
	fdata.close();
	return true;
}

bool Manager::PRINT_ITEMLIST() {
	return fpgrowth->printList();
}

bool Manager::PRINT_FPTREE() {
	return fpgrowth->printTree();;
}

bool Manager::PRINT_MIN(char* item, int min_frequency) {
	if (bptree == NULL) return false; //no BpTree
	return bptree->printFrequency(item, min_frequency);
}

bool Manager::PRINT_CONFIDENCE(char* item, double rate) {
	if (bptree == NULL) return false; //no BpTree
	//find item frequncy
	int itemFreq = fpgrowth->getHeaderTable()->find_frequency((string)item);
	double minFreq = rate * itemFreq;

	return bptree->printConfidence(item, itemFreq, minFreq);
}

bool Manager::PRINT_RANGE(char* item, int start, int end) {
	if (bptree == NULL) return false; //no BpTree
	return bptree->printRange((string)item, start, end);;
}

void Manager::printErrorCode(int n) {	//ERROR CODE PRINT
	flog << "======== ERROR " << n << " ========" << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}


