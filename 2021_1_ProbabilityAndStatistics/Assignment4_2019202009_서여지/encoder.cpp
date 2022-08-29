#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <map>
using namespace std;

#define trainingText "training_input.txt"
#define test1Text "test_input1.txt"
#define test2Text "test_input2.txt"
#define test3Text "test_input3.txt"

#define aTableHBS "context_adaptive_huffman_table.hbs"
#define nTableHBS "huffman_table.hbs"

#define trainingHBS "training_input_code.hbs"
#define test1HBS "test_input1_code.hbs"
#define test2HBS "test_input2_code.hbs"
#define test3HBS "test_input3_code.hbs"

#define nTableFlag	1
#define ASCIIFlag	2


struct Node { // huffman tree node
	char preCh;
	char ch;
	int p;
	struct Node* rightNode;
	struct Node* leftNode;
};

struct compare { // priority queue
	bool operator()(const struct Node* node1, const struct Node* node2) {
		return node1->p > node2->p;
	}
};

struct Node* makeNode(char pre, char ch, int p) {
	struct Node* tmp = new struct Node;
	tmp->preCh = pre;
	tmp->ch = ch;
	tmp->p = p;
	tmp->rightNode = NULL;
	tmp->leftNode = NULL;
	return tmp;
}

struct Node* makeNode(char pre, int p, struct Node* left, struct Node* right) {
	struct Node* tmp = new struct Node;
	tmp->preCh = pre;
	tmp->ch = NULL;
	tmp->p = p;
	tmp->rightNode = right;
	tmp->leftNode = left;
	return tmp;
}

void setFlag(int(*arr)[128]) {
	for (int i = 0; i < 128; i++) { //to use nTable instead adTable
		if (arr[0][i]) arr[i][nTableFlag]++;
	}
	arr[0][0x1A]++; //EOD
	arr[0][ASCIIFlag]++; //use ASCII code instead codeword
}

//save each char count in arr
void countChar(int(*arr)[128]) {
	FILE* inputFile = NULL;
	if (fopen_s(&inputFile, trainingText, "rt")) { //open file
		cout << "ERROR: no [" << trainingText << "] file" << endl;
		exit(-1);
	}
	char pre = NULL, ch = NULL;
	while ((ch = fgetc(inputFile)) != EOF) {
		arr[0][ch]++; // character count +1
		if (pre) arr[pre][ch]++;
		pre = ch;
	}
	fclose(inputFile); //close file

	setFlag(arr);
	return;
}

// priority queue -> huffmanTree
void makeHuffmanTree(priority_queue<struct Node*, vector<struct Node*>, struct compare>* que) {
	struct Node* Ltmp = NULL;
	struct Node* Rtmp = NULL;
	char pre = NULL;
	while ((*que).size() > 1) {
		if ((*que).top()->p == 0) { // p(ch) = 0, no occur
			(*que).pop();
			continue;
		}
		pre = (*que).top()->preCh;
		Ltmp = (*que).top(); (*que).pop(); //left child
		Rtmp = (*que).top(); (*que).pop(); //right child
		(*que).push(makeNode(pre, Ltmp->p + Rtmp->p, Ltmp, Rtmp)); //push new node
	}
}

// huffman tree -> encored codeword
char look(struct Node* node, unsigned int codeword, int codeLen, map<char, pair<int, int>>* table) {
	if (node->ch) {
		table->insert(make_pair(node->ch, pair<int, int>(codeLen, codeword))); // insert map
		return node->preCh;
	}
	if (node->leftNode) {
		int tmp = codeword << 1; //push_back (0)
		look(node->leftNode, tmp, codeLen + 1, table);
	}
	if (node->rightNode) {
		int tmp = (codeword << 1) + 1; //push_back (1)
		look(node->rightNode, tmp, codeLen + 1, table);
	}
}

//write binary file
int writeBuf(FILE* outputFile, unsigned long long int* buf, int count) {
	unsigned char tmp = 0; //(1byte)
	while (count > 7) {
		tmp = *buf >> (count - 8);
		fwrite(&tmp, 1, 1, outputFile);		//  1byte write
		count -= 8;
	}
	return count;
}

// table map -> normal huffman table file
void makeNTableFile(map<char, pair<int, int>>* table) {
	FILE* tableFile = NULL;
	if (fopen_s(&tableFile, nTableHBS, "wb")) { //make file
		cout << "ERROR: can't make [" << nTableHBS << "] file" << endl;
		exit(-1);
	}
	map<char, pair<int, int>>::iterator iter;
	unsigned char tmp = 0; //(1byte)
	unsigned long long int buf = 0; //(8byte)
	int count = 0;
	for (iter = table->begin(); iter != table->end(); iter++) {
		buf <<= 8; buf += iter->first; count += 8;				//ch <<1 byte
		tmp = iter->second.first;								//size <<1 byte
		buf <<= 8; buf += tmp; count += 8;	 
		buf <<= tmp; buf += iter->second.second; count += tmp;	// codeword
		count = writeBuf(tableFile, &buf, count);
	}
	if (count > 0) { //align
		tmp = buf <<= (8 - count);
		fwrite(&tmp, 1, 1, tableFile);		//  1byte write
	}
	fclose(tableFile); //close file
}

// table map -> context adaptive huffman table file
void makeATableFile(map <char, map<char, pair<int, int>>>* tableMap) {
	FILE* tableFile = NULL;
	if (fopen_s(&tableFile, aTableHBS, "wb")) { //make file
		cout << "ERROR: can't open [" << aTableHBS << "] file" << endl;
		exit(-1);
	}

	map <char, map<char, pair<int, int>>>::iterator mapIter;
	map<char, pair<int, int>>::iterator iter;
	unsigned char tmp = 0; //(1byte)
	unsigned long long int buf = 0; //(8byte)
	int count = 0;
	int EODsize = 0,  EODcode = 0;

	buf <<= 8; buf += tableMap->size()-1; count += 8;		//the number of tables <<1 byte
	for (mapIter = tableMap->begin(); mapIter != tableMap->end(); mapIter++) {
		if (mapIter->first == NULL) {
			EODsize = mapIter->second.find(0x1A)->second.first;
			EODcode = mapIter->second.find(0x1A)->second.second;
			continue;
		}
		buf <<= 8; buf += mapIter->first; count += 8;		//preceding symbol <<1 byte
		for (iter = mapIter->second.begin(); iter != mapIter->second.end(); iter++) {
			buf <<= 8; buf += iter->first; count += 8;					//ch <<1 byte
			tmp = iter->second.first;
			buf <<= 8; buf += tmp;  count += 8;							//size <<1 byte
			buf <<= tmp; buf += iter->second.second; count += tmp;		// codeword<< 1~3 byte
			
			if (++iter == mapIter->second.end()) { //EOD
				buf <<= EODsize; buf += EODcode; count += EODsize;		//EOD codeword
			}
			iter--;
			count = writeBuf(tableFile, &buf, count);
		} 
	}
	if (count > 0) { //align
		tmp = buf <<= (8 - count); count += (8 - count);
		fwrite(&tmp, 1, 1, tableFile);		//  1byte write
		count -= 8;
	}
	fclose(tableFile); //close file
}

// table map -> huffman code
void writeHuffmanCode(const char*inTXT, const char* outHBS, map <char, map<char, pair<int, int>>>* tableMap) {
	FILE* inputFile = NULL;
	if (fopen_s(&inputFile, inTXT, "rt")) { //open file
		cout << "ERROR: no [" << inTXT << "] file" << endl;
		exit(-1);
	}
	FILE* outputFile = NULL;
	if (fopen_s(&outputFile, outHBS, "wb")) { //make file
		cout << "ERROR: can't make [" << outHBS << "] file" << endl;
		exit(-1);
	}
	char pre = NULL, ch = NULL;
	unsigned char tmp = 0; //(1byte)
	unsigned long long int buf = 0; //(8byte)
	int count = 0, nFlag = 0, AFlag = 0;
	map <char, map<char, pair<int, int>>>::iterator table;
	map<char, pair<int, int>>::iterator iter;

	int EODcode, EODsize;
	EODsize = tableMap->find(NULL)->second.find(0x1A)->second.first;
	EODcode = tableMap->find(NULL)->second.find(0x1A)->second.second;

	cout << endl<<endl<<inTXT << endl;

	ch = fgetc(inputFile); 
	table = tableMap->find(NULL); iter = table->second.find(ch);
	buf += iter->second.second;	 count += iter->second.first; // first char
	pre = ch; 
	while ((ch = fgetc(inputFile)) != EOF) {
		if (tableMap->find(pre) == tableMap->end()) pre = NULL;
		table = tableMap->find(pre); iter = table->second.find(ch); 
		if (iter == table->second.end()) {
			if (pre) {	// nTable instead aTable
				table = tableMap->find(pre); iter = table->second.find(1); //normal table Flag
				buf <<= iter->second.first; buf += iter->second.second; count += iter->second.first; 
				nFlag++;
				pre = NULL;
				table = tableMap->find(NULL); iter = table->second.find(ch);
			}
			if ((!pre)&&(iter == table->second.end())) {// ASCII instead codeword
				table = tableMap->find(pre); iter = table->second.find(2);//ASCII Flag
				buf <<= iter->second.first;	 buf += iter->second.second; count += iter->second.first;
				AFlag++;
				buf <<= 8; buf += ch; count += 8;		//ASCII code
				count = writeBuf(outputFile, &buf, count);
				continue;
			}
		}
		buf <<= iter->second.first; buf += iter->second.second; count += iter->second.first; //codeword
		count = writeBuf(outputFile, &buf, count);
		pre = ch;
	}
	buf <<= EODsize; buf += EODcode; count += EODsize; //EOD
	count = writeBuf(outputFile, &buf, count);
	if (count > 0) { //align
		buf <<= (8 - count);
		tmp = 0xFFFF; tmp &= buf;
		fwrite(&tmp, 1, 1, outputFile);		//  1byte write
	}
	fclose(inputFile); //close file
	fclose(outputFile);
	cout << "normal: " << nFlag << "\tASCII: " << AFlag << endl;
}

//make 128*128 tree node
void makeTreeNode( map < char, priority_queue<struct Node*, vector<struct Node*>, struct compare>>* queMap,
					int(*arr)[128]) {
	priority_queue<struct Node*, vector<struct Node*>, struct compare>* qptr = NULL;
	for (int i = 0; i < 128; i++) {
		qptr = new priority_queue<struct Node*, vector<struct Node*>, struct compare>;
		for (int j = 0; j < 128; j++) qptr->push(makeNode(i, j, arr[i][j]));
		queMap->insert(make_pair(i, *qptr));
	}
}

void makeTableMap(map <char, map<char, pair<int, int>>>* tableMap,
					map < char, priority_queue<struct Node*, vector<struct Node*>, struct compare>>* queMap)
{
	map <char, pair<int, int>>* mptr = NULL;
	map < char, priority_queue<struct Node*, vector<struct Node*>, struct compare>>::iterator iter;
	char preCh = NULL;
	for (iter = queMap->begin(); iter != queMap->end(); iter++) {
		mptr = new map<char, pair<int, int>>;
		preCh = look(iter->second.top(), 0, 0, mptr);
		tableMap->insert(make_pair(preCh, *mptr));
	}
}

int main(void) {
	int arr[128][128] = { 0 };
	countChar(arr);

	map < char, priority_queue<struct Node*, vector<struct Node*>, struct compare>> queMap;
	makeTreeNode(&queMap,arr);

	/*
	priority_queue <int> ique;
	for (int i = 0; i < 128; i++)  ique.push(arr[0][i]);
	for (int i = 0; i < 31; i++)ique.pop();
	int k = ique.top();
	*/

	int tmp = queMap.size();
	for (int i = 0; i < tmp; i++) {
		makeHuffmanTree(&queMap[i]);
		if (queMap[i].top()->p < 1) queMap.erase(i);
		//else { if((arr[0][i]<k)&&(i!=NULL)) queMap.erase(i); }
	}

	map <char, map<char, pair<int, int>>> tableMap;
	makeTableMap(&tableMap, &queMap);

	cout <<endl<<"tableMap size: "<< tableMap.size()-1 << endl;

	makeNTableFile(&tableMap[NULL]);
	makeATableFile(&tableMap);

	writeHuffmanCode(trainingText, trainingHBS, &tableMap);
	writeHuffmanCode(test1Text, test1HBS, &tableMap);
	writeHuffmanCode(test2Text, test2HBS, &tableMap);
	writeHuffmanCode(test3Text, test3HBS, &tableMap);
	return 0;
}