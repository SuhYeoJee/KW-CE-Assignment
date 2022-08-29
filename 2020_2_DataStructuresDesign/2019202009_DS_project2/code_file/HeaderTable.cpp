#include "HeaderTable.h"

HeaderTable::~HeaderTable() {

}

void HeaderTable::insertTable(char* item, int frequency) {
	if (indexTable.empty()) {
		indexTable.push_back(make_pair(frequency, (string)item)); //indexTable empty
		dataTable.insert(make_pair(item, nullptr));
	}
	else if(!find_frequency(item)){
		indexTable.push_back(make_pair(frequency, (string)item));  //no item in indext table
		dataTable.insert(make_pair(item, nullptr));
	}
	else { //item exist
		// FPNode freq +1
		if((dataTable.find(item)!=dataTable.end())&&(dataTable.find(item)->second!=NULL))
			dataTable.find(item)->second->updateFrequency(1);
		// indextTable frequency+1
		list<pair<int, string> >::iterator it;
		for (it = indexTable.begin(); it != indexTable.end(); it++)
			if ((*it).second == item) break;
		int tempFreq = (*it).first;
		indexTable.insert(it, make_pair(tempFreq+frequency, item));
		indexTable.erase(it);
	}
}

int HeaderTable::find_frequency(string item){
	//return frequency. if no item, return 0
	list<pair<int, string> >::iterator it;
	for (it = indexTable.begin(); it != indexTable.end(); it++)
		if ((*it).second == item) break;
	if (it != indexTable.end()) return (*it).first;
	else return 0;
}

