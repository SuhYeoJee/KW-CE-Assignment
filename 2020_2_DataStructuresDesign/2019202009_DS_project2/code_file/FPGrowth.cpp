#include "FPGrowth.h"
#include <functional>

FPGrowth::~FPGrowth() {

}

void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) {
	FPNode* curNode = root, *tempNode;
	string item;
	while (!item_array.empty()) {
		item = item_array.front(); //get item
		if (table->find_frequency(item) < threshold);
		else if (tempNode = curNode->getChildrenNode(item)) { //tree has item node
			tempNode->updateFrequency(frequency);
			curNode = tempNode;
		}
		else { //no item node
			tempNode = new FPNode;	//make new node
			connectNode(table, item, tempNode);
			tempNode->setItem((char*)item.c_str());
			tempNode->setParent(curNode);
			tempNode->updateFrequency(frequency);
			curNode->pushchildren(item, tempNode);
			curNode = tempNode;
		}
		item_array.pop_front(); //to next item
	}
	exist = true;	//now tree is exist
}

void FPGrowth::connectNode(HeaderTable* table, string item, FPNode* node) {
	FPNode* tempNode = table->getdataTable()[item]; // connect FPNode
	if(tempNode==NULL) table->dataTableConnect(item, node); //first FPNode
	else {
		while(tempNode->getNext() != NULL) { //find tail of linked list
			tempNode = tempNode->getNext();
		}
		tempNode->setNext(node);
	}
}


//////////////////////////////////
bool FPGrowth::contains_single_path(FPNode* pNode) {
	if (pNode->getChildren().size() == 0) return true;
	else if (pNode->getChildren().size() > 1) return false;
	return contains_single_path(pNode->getChildren().begin()->second);
}
map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable* pTable, FPNode* pTree) {

	return {};
}
void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) {
	if (data.size() == depth) {
		set<string> set; set.insert(item);
		for (int i = 0; i < data.size(); i++) { if (ptr[i] == 1) set.insert(data[i]); }
		FrequentPattern->insert(make_pair(set, frequency)); return;
	}
	ptr[depth] = 1;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
	ptr[depth] = 0;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
}
void FPGrowth::saveFrequentPatterns() {

}
//////////////////////////////////


bool FPGrowth::printList() {
	if (getHeaderTable()->getindexTable().empty()) return false; //no table
	getHeaderTable()->descendingIndexTable();
	list<pair<int, string>> it = getHeaderTable()->getindexTable();
	pair<int, string> indexnode = it.front();
	*fout << "Item\tFrequency" << endl;
	while (!it.empty()) { //for all element in indexTable
		indexnode = it.front();
		*fout << indexnode.second << ' ' << indexnode.first << endl;
		it.pop_front();
	}
	*fout << "=======================" << endl << endl;
	return true;
}
bool FPGrowth::printTree() {
	if (getTree()->getChildren().empty()) return false; //empty tree

	*fout << "{StandardItem,Frequency} (Path_Item,Frequency)" << endl;
	getHeaderTable()->ascendingIndexTable(); //indexTable sort
	list<pair<int, string>> it = getHeaderTable()->getindexTable();

	while (!it.empty()) { //for all element in indexTable
		if (it.front().first < threshold) { it.pop_front(); continue; }
		*fout << '{' << it.front().second << ',' << it.front().first << '}' << endl;
		FPNode* node = (*(getHeaderTable()->getdataTable().find(it.front().second))).second;
		while (node != nullptr) { //for every node linked by dataTable
			FPNode* temp = node;
			while (temp != nullptr) { //from item node to root node
				if (temp == fpTree) break; //root node
				*fout << '(' << temp->getItem() << ',' << temp->getFrequency() << ") ";
				temp = temp->getParent();
			}
			node = node->getNext();
			*fout << endl;
		}
		it.pop_front();
	}
	*fout << "=======================" << endl << endl;
	return true;
}
