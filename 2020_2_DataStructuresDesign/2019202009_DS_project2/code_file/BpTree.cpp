#include "BpTree.h"

bool BpTree::Insert(int key, set<string> set) {
	BpTreeNode* dataNode = searchDataNode(key);
	map <int, FrequentPatternNode*>::iterator it;
	if (!dataNode) { //new BPTREE
		root = new BpTreeDataNode;
		FrequentPatternNode* patternNode = new FrequentPatternNode;
		patternNode->setFrequency(key);	//set data
		patternNode->InsertList(set);
		root->insertDataMap(key, patternNode);
		return true;
	}

	it = dataNode->getDataMap()->find(key); 
	if (it != dataNode->getDataMap()->end()) //patternNode exist
		(*it).second->InsertList(set);	//insert data

	else{ //make new patternNode
		FrequentPatternNode* patternNode = new FrequentPatternNode;
		patternNode->setFrequency(key);	//set data
		patternNode->InsertList(set);
		dataNode->insertDataMap(key, patternNode);
		if (excessDataNode(dataNode)) 
			splitDataNode(dataNode);
	}
	return true;
}

BpTreeNode* BpTree::searchDataNode(int n) {
	BpTreeNode* pCur = root;
	if (!root) return NULL; //no tree
	map <int, BpTreeNode*>::iterator it, itEnd;

	while (pCur->IsIndex()) { //for each index node
		it = pCur->getIndexMap()->begin();
		itEnd = pCur->getIndexMap()->end();
		for (it; it != itEnd;it++) { //for every BpTreeNode in index node
			if ((*it).first == NULL) continue;
			if (n < (*it).first) { //to child
				if (it == pCur->getIndexMap()->begin()) {
					pCur = pCur->getMostLeftChild();
					break;
				}
				else {
					pCur = (*(--it)).second;
					break;
				}
			}
			if (!pCur->IsIndex()) return pCur; //return dataNode
		}
		if(it==itEnd) pCur = (*(--it)).second;
	}
	return pCur; //return dataNode
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	map <int, FrequentPatternNode*>::iterator it, it2;
	int splitKey = ceil((order - 1) / 2.0) + 1;
	BpTreeNode* newNode = new BpTreeDataNode;

	if (!pDataNode->getParent()) { //root split
		BpTreeIndexNode* newIndex = new BpTreeIndexNode;
		root = newIndex;
		root->setMostLeftChild(pDataNode);
		pDataNode->setParent(root);
	}

	it = pDataNode->getDataMap()->begin();
	for (int i = 1; i < splitKey; i++) { it++; }
	it2 = it;
	int freq = (*it).first;

	//ptr -> parent, next, pre		//no child(data node)
	newNode->setParent(pDataNode->getParent());
	if (pDataNode->getNext()) { 
		newNode->setNext(pDataNode->getNext()); 
		newNode->getNext()->setPrev(newNode);
	}
	pDataNode->setNext(newNode);
	newNode->setPrev(pDataNode);

	//pDataNode --data--> newNode
	for (it; it != pDataNode->getDataMap()->end(); it++) {
		newNode->insertDataMap((*it).first, (*it).second);
	}
	it = it2;	//delete data in pDataNode
	for (it; it != pDataNode->getDataMap()->end();) {
		it2 = it; it++;
		pDataNode->deleteMap((*it2).first);
	}

	pDataNode->getParent()->insertIndexMap(freq, newNode); //index node
	if (excessIndexNode(pDataNode->getParent())) 
		splitIndexNode(pDataNode->getParent()); //index node split
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	//split(ceil((order-1)/2.0)+1)
	map <int, BpTreeNode*>::iterator it, it2;
	int splitKey = ceil((order - 1) / 2.0) + 1;
	BpTreeNode* newNode = new BpTreeIndexNode;
	//insert data
	
	it = pIndexNode->getIndexMap()->begin();
	for (int i = 1; i < splitKey; i++) { it++; }
	it2 = it; 
	newNode->setMostLeftChild((*it).second);
	newNode->getMostLeftChild()->setParent(newNode);
	int freq = (*it).first;

	//pIndexNode --data--> newNode
	for (it++; it != pIndexNode->getIndexMap()->end(); it++) {
		newNode->insertIndexMap((*it).first, (*it).second);
		(*it).second->setParent(newNode);
	}
	it = it2;	 //delete data in pIndexNode
	for (it; it != pIndexNode->getIndexMap()->end();) {
		it2 = it; it++;
		pIndexNode->deleteMap((*it2).first);
	}

	//ptr -> parent, child
	if (!pIndexNode->getParent()) { // root split -> make new root
		root = new BpTreeIndexNode;
		root->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(root);
		root->insertIndexMap(freq, newNode);
		newNode->setParent(root);
		return;
	}
	newNode->setParent(pIndexNode->getParent());
	//indexnode insert
	pIndexNode->getParent()->insertIndexMap(freq, newNode);
	if (excessIndexNode(pIndexNode->getParent()))
		splitIndexNode(pIndexNode->getParent()); //indexnode split
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}
bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}


bool BpTree::printConfidence(string item, double item_frequency, double min_frequency)
{
	if (!root) return false;

	///////////////////////////////

	int max; int min = ceil(min_frequency);
	BpTreeNode* temp = root;
	while (temp->IsIndex()) {
		temp = temp->getMostLeftChild();
	}//temp is first dataNode
	while (temp->getNext()) {
		temp = temp->getNext();
	}//temp is last dataNode
	max = (*(--(temp->getDataMap()->end()))).first;

	////////////// use printFrequency() /////////////////

	//print min to max
	BpTreeNode* dataNode;
	set<string> patternSet;
	set<string> ::iterator patternItem;
	multimap<int, set<string> > patternList; //first: size
	multimap<int, set<string> >::iterator itMap;
	bool result = false;
	
	////////////// use printRange() /////////////////

	for (int i = min; i <= max; i++) {//for given range
		dataNode = searchDataNode(i);
		if (!dataNode) continue; //no dataNode
		if ((dataNode->getDataMap()->find(i)) != dataNode->getDataMap()->end()) 
			patternList = (*dataNode->getDataMap()->find(i)).second->getList(); //freq:i node exist
		else continue;
		itMap = patternList.begin();
		for (itMap; itMap != patternList.end(); itMap++) { //find set including item
			patternSet = (*itMap).second;
			if (patternSet.find(item) == patternSet.end()) continue; //no item in set
			if (!result) { 
				*fout <<"StandardItem	FrequentPattern	Confidence" << endl; 
				result = true;
			}
			double confidence = i / item_frequency;
			patternSet.erase(item); *fout << item << " -> {";
			patternItem = patternSet.begin();
			for (patternItem; patternItem != patternSet.end();) { // every element in patternSet
				*fout << (*patternItem);
				if (++patternItem != patternSet.end())
					*fout << ", ";
				else {
					(*fout).precision(2);
					*fout << "} " << i << ' ' << confidence << endl;
				}
			}
		}
		
	}
	if(result)*fout << "=======================" << endl << endl;
	return result;
}
bool BpTree::printFrequency(string item, int min_frequency)//print winratio in ascending order
{
	if (!root) return false; //no BpTree
	int end;	//find list dataNode's frequency
	BpTreeNode* temp = root;
	while (temp->IsIndex()) {
		temp = temp->getMostLeftChild();
	}//temp is first dataNode
	while (temp->getNext()) {
		temp = temp->getNext();
	}//temp is last dataNode
	end = (*(--(temp->getDataMap()->end()))).first;
	return printRange(item, min_frequency, end);
}
bool BpTree::printRange(string item, int min, int max) {
	if (!root) return false; //no BpTree
	//print min to max
	BpTreeNode* dataNode;
	set<string> patternSet;
	set<string> :: iterator patternItem;
	multimap<int, set<string> > patternList; //first: size
	multimap<int, set<string> >::iterator itMap;
	bool result = false;
	
	for (int i = min; i <= max; i++) { //for given range
		dataNode = searchDataNode(i);
		if (!dataNode) continue; //no dataNode
		if ((dataNode->getDataMap()->find(i)) != dataNode->getDataMap()->end()) //freq:i node exist
			patternList = (*dataNode->getDataMap()->find(i)).second->getList();
		else continue;
		itMap = patternList.begin(); //head of list
		for (itMap; itMap != patternList.end(); itMap++) {
			patternSet = (*itMap).second;
			if (patternSet.find(item) == patternSet.end()) continue; //no item in set
			// print
			if (!result) {
				*fout <<"StandardItem	FrequentPatternFrequency" << endl;
				result = true;
			}
			patternSet.erase(item); *fout << item<<" -> {";
			patternItem = patternSet.begin();
			for (patternItem; patternItem != patternSet.end();) { // every element in patternSet
				*fout << (*patternItem);
				if (++patternItem != patternSet.end())
					*fout << ", ";
				else *fout << "} " << i << endl;
			}
		}
	}
	if(result)*fout << "=======================" << endl << endl;
	return result;
}
void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item) {
	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	curPattern.erase(item);
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) { //for every element in set
		string temp = *it++;
		if (temp != item) *fout << temp;
		if (it == curPattern.end()) { //end print
			*fout << "} ";
			break;
		}
		*fout << ", ";
	}
	*fout << "=======================" << endl << endl;
}

