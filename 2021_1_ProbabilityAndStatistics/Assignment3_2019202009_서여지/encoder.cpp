#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <map>
using namespace std;

#define inputTextFile "input.txt"
#define tableHBSFile "huffman_table.hbs"
#define outputHBSFile "huffman_code.hbs"

struct Node { // huffman tree node
	char ch;
	float p;
	struct Node* rightNode;
	struct Node* leftNode;
};

struct compare { // priority queue
	bool operator()(const struct Node* node1, const struct Node* node2) {
		return node1->p > node2->p;
	}
};

struct Node* makeNode(char ch, float p) {
	struct Node* tmp = new struct Node;
	tmp->ch = ch;
	tmp->p = p;
	tmp->rightNode = NULL;
	tmp->leftNode = NULL;
	return tmp;
}

struct Node* makeNode(float p, struct Node* left, struct Node* right) {
	struct Node* tmp = new struct Node; 
	tmp->ch = NULL;
	tmp->p = p;
	tmp->rightNode = right;
	tmp->leftNode = left;
	return tmp;
}

//return total char count
//save each char count in arr
int countChar(float* arr) {
	FILE* inputFile = NULL;
	if (fopen_s(&inputFile, inputTextFile, "rt")) { //open file
		cout << "ERROR: no [" << inputTextFile << "] file" << endl;
		exit(-1);
	}
	else {
		int count = 0;
		char ch = NULL;
		while ((ch = fgetc(inputFile)) != EOF) {
			count++; //total count +1
			arr[ch]++; // character count +1
		}
		count++; arr[0x1A]++; //EOF
		fclose(inputFile); //close file
		return count;
	}
}

// huffman tree -> encored codeword
void look(struct Node* node, unsigned int codeword, int codeLen, map<char, pair<int, int>>* table) {
	if (node->ch) {
		table->insert(make_pair(node->ch, pair<int, int>(codeLen, codeword))); // insert map
		return;
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

// table map -> .hbs file
void makeTableFile(map<char, pair<int, int>>* table) {
	FILE* tableFile = NULL;
	if (fopen_s(&tableFile, tableHBSFile, "wb")) { //make file
		cout << "ERROR: can't make [" << tableHBSFile << "] file" << endl;
		exit(-1);
	}
	else {
		map<char, pair<int, int>>::iterator iter;
		unsigned char tmp = 0; //(1byte)
		unsigned long long int buf = 0; //(8byte)
		int count = 0;
		for (iter = table->begin(); iter != table->end(); iter++) {
			buf <<= 8;
			buf += iter->first; buf <<= 8; count += 8;		//ch <<1 byte
			tmp = iter->second.first;
			buf += tmp; buf <<= tmp; count += 8;		//size <<1 byte
			buf += iter->second.second;				// codeword
			count += tmp;	//size << 1~3 byte
			while (count > 7) {
				tmp = buf>>(count-8);
				fwrite(&tmp, 1, 1, tableFile);		//  1byte write
				count -= 8;
			}
		}
		if (count > 0) { //align
			tmp = buf <<= (8-count);
			fwrite(&tmp, 1, 1, tableFile);		//  1byte write
		}
		fclose(tableFile); //close file
	}
}

// priority queue -> huffmanTree
void makeHuffmanTree(priority_queue<struct Node*, vector<struct Node*>, struct compare>* que) {
	struct Node* Ltmp = NULL;
	struct Node* Rtmp = NULL;
	while ((*que).size() > 1) {
		if ((*que).top()->p == 0) { // p(ch) = 0, no occur
			(*que).pop();
			continue;
		}
		Ltmp = (*que).top(); (*que).pop(); //left child
		Rtmp = (*que).top(); (*que).pop(); //right child
		(*que).push(makeNode(Ltmp->p + Rtmp->p, Ltmp, Rtmp)); //push new node
	}
}

// table map -> huffman code
void writeHuffmanCode(map<char, pair<int, int>>* table) {
	FILE* inputFile = NULL;
	if (fopen_s(&inputFile, inputTextFile, "rt")) { //open file
		cout << "ERROR: no [" << inputTextFile << "] file" << endl;
		exit(-1);
	}
	FILE* outputFile = NULL;
	if (fopen_s(&outputFile, outputHBSFile, "wb")) { //make file
		cout << "ERROR: can't make [" << outputHBSFile << "] file" << endl;
		exit(-1);
	}
	char ch = NULL;
	unsigned char tmp = 0; //(1byte)
	unsigned long long int buf = 0; //(8byte)
	int count = 0;
	map<char, pair<int, int>>::iterator iter;
	while ((ch = fgetc(inputFile)) != EOF) {
		iter = table->find(ch);
		buf <<= iter->second.first; // to get codeword

		buf += iter->second.second;				// codeword
		count += iter->second.first;			//size << 1~3 byte

		while (count > 7) {
			tmp = buf >> (count - 8);
			fwrite(&tmp, 1, 1, outputFile);		//  1byte write
			count -= 8;
		}
	}

	iter = table->find(0x1A);	//EOF
	if (count > 0) buf <<= iter->second.first; // to get codeword
	buf += iter->second.second;				// codeword
	count += iter->second.first;			//size << 1~3 byte

	while (count > 7) {
		tmp = buf >> (count - 8);
		fwrite(&tmp, 1, 1, outputFile);		//  1byte write
		count -= 8;
	}
	if (count > 0) { //align
		buf <<= (8 - count);
		tmp = 0xFFFF; tmp &= buf;
		fwrite(&tmp, 1, 1, outputFile);		//  1byte write
	}
	fclose(inputFile); //close file
	fclose(outputFile); 
}

int main(void) {
	float arr[128] = { 0 };
	int count = countChar(arr);

	//make 128 tree node
	priority_queue<struct Node*, vector<struct Node*>, struct compare> que;
	for (int i = 0; i < 128; i++) que.push(makeNode(i, arr[i] / count));

	makeHuffmanTree(&que);

	map<char, pair<int, int>> table;
	look(que.top(), 0, 0, &table);
	makeTableFile(&table);

	writeHuffmanCode(&table);
	return 0;
}