#include <iostream>
#include <string>
#include <map>
using namespace std;

#define trainingHBS "training_input_code.hbs"
#define test1HBS "test_input1_code.hbs"
#define test2HBS "test_input2_code.hbs"
#define test3HBS "test_input3_code.hbs"

#define aTableHBS "context_adaptive_huffman_table.hbs"
#define nTableHBS "huffman_table.hbs"

#define trainingText "training_output.txt"
#define test1Text "test_output1.txt"
#define test2Text "test_output2.txt"
#define test3Text "test_output3.txt"

#define nTableFlag	1
#define ASCIIFlag	2

// table.hbs -> table map
void readTable(map<char, pair<int, int>>* table) { //map<char, pair<int, int>> ch, codeword, size
	FILE* tableFile = NULL;
	if (fopen_s(&tableFile, nTableHBS, "rb")) { //open table
		cout << "ERROR: no [" << nTableHBS << "] file" << endl;
		exit(-1);
	}
	else {
		char ch = NULL;
		char bitSize = 0;
		unsigned int codeword = 0;
		unsigned long long int buf = 0; //(8byte)
		int count = 0;
		int te = 0;

		while (1) {
			while (count < 40) { //( ch 1 byte, size 1 byte, codeword 1~3 byte
				buf <<= 8;
				fread_s(&buf, sizeof(buf), 1, 1, tableFile);
				count += 8;
			}

			ch = buf >> (count - 8); count -= 8; // ch
			if (ch == 0) break; //file end
			bitSize = buf >> (count - 8); count -= 8; // size

			codeword = 0xFFFFFFFF;
			codeword >>= (32 - bitSize);
			codeword &= buf >> (count - bitSize); count -= bitSize; // codeword

			table->insert(make_pair(ch, make_pair(codeword, bitSize)));
		}
		fclose(tableFile); //close file
		return;	//EOF
	}
}

// table.hbs -> table map
void readTable(map<char, map<char, pair<int, int>>>* tableMap, int EODsize, int EODcode) {//preCh, ch, codeword, size
	FILE* tableFile = NULL;
	if (fopen_s(&tableFile, aTableHBS, "rb")) { //open table
		cout << "ERROR: no [" << aTableHBS << "] file" << endl;
		exit(-1);
	}

	char ch = NULL, preCh = NULL;
	unsigned int tmp = 0;
	char bitSize = 0;
	unsigned int codeword = 0;
	unsigned long long int buf = 0; //(8byte)
	int count = 0;
	int tableCount = 0;
	map<char, pair<int, int>>* mptr = NULL;

	fread_s(&tableCount, sizeof(tableCount), 1, 1, tableFile);
	for (int i = 0; i < tableCount; i++) {
		mptr = new map<char, pair<int, int>>;
		buf <<= 8;
		fread_s(&buf, sizeof(buf), 1, 1, tableFile);
		count += 8;
		preCh = buf >> (count - 8); count -= 8;
		while (1) {
			while (count < 40) { //( ch 1 byte, size 1 byte, codeword 
				buf <<= 8;
				fread_s(&buf, sizeof(buf), 1, 1, tableFile);
				count += 8;
			}
			tmp = 0xFFFFFFFF; tmp >>= (32 - EODsize);
			tmp &= buf >> (count - EODsize);
			if (tmp == EODcode) {
				count -= EODsize;
				break;
			}
			ch = buf >> (count - 8); count -= 8; // ch
			bitSize = buf >> (count - 8); count -= 8; // size

			codeword = 0xFFFFFFFF;
			codeword >>= (32 - bitSize);
			codeword &= buf >> (count - bitSize); count -= bitSize; // codeword

			mptr->insert(make_pair(ch, make_pair(codeword, bitSize)));
		}
		tableMap->insert(make_pair(preCh, *mptr));
	}
	fclose(tableFile); //close file
	return;
}


// table map -> output.txt

void writeOutput(const char* inHBS, const char* outTXT, map<char, map<char, pair<int, int>>>* tableMap) {
	FILE* inputFile = NULL;
	if (fopen_s(&inputFile, inHBS, "rb")) { //open file
		cout << "ERROR: no [" << inHBS << "] file" << endl;
		exit(-1);
	}
	FILE* outputFile = NULL;
	if (fopen_s(&outputFile, outTXT, "wt")) { //make file
		cout << "ERROR: can't make [" << outTXT << "] file" << endl;
		exit(-1);
	}
	cout << outTXT << endl;
	char pre = NULL;
	unsigned char tmp = 0; //(4byte)
	unsigned long long int buf = 0; //(8byte)
	int count = 0, size = 0, nFlag = 0, AFlag = 0;
	unsigned int mask = 0xFFFFFFFF;
	map<char, pair<int, int>>::iterator iter;
	map<char, map<char, pair<int, int>>>::iterator table;
	int EODcode, EODsize;
	EODcode = tableMap->find(NULL)->second.find(0x1A)->second.first;
	EODsize = tableMap->find(NULL)->second.find(0x1A)->second.second;

	table = tableMap->find(NULL); 
	while (1) {
		while (count < 24) {
			buf <<= 8;
			fread_s(&tmp, sizeof(tmp), 1, 1, inputFile);
			buf += tmp;
			count += 8;
		}
		mask = 0xFFFFFFFF; // check EOD
		mask >>= (32 - EODsize);
		mask &= buf >> (count - EODsize);
		if ((mask == EODcode) && (feof(inputFile))) break;

		mask = 0xFFFFFFFF;
		mask >>= (32 - ++size);		//1, 2, 3,,,
		mask &= buf >> (count - size);
		for (iter = table->second.begin(); iter != table->second.end(); iter++) {
			if ((iter->second.first == mask) && (iter->second.second == size))
				break;
		}

		if (iter == table->second.end()) continue;
		if (iter->first == 1) { // use normal table
			nFlag++;
			count -= size; size = 0; pre = NULL;
			table = tableMap->find(pre);
			iter = table->second.begin();
			continue;
		}
		if (iter->first == 2) { // use ASCII code
			AFlag++;
			count -= size; size = 0; pre = NULL;

			if (count < 8) {
				buf <<= 8;
				fread_s(&tmp, sizeof(tmp), 1, 1, inputFile);
				buf += tmp;
				count += 8;
			}
			
			mask = 0x000000FF; // read 8 bit
			mask &= buf >> (count - 8); count -= 8;

			fputc(mask, outputFile);
			
			table = tableMap->find(pre);
			iter = table->second.begin();
			continue;
		}

		do {
			fputc(iter->first, outputFile);
			count -= size;
			size = 0;
			pre = iter->first;
			if (tableMap->find(pre) == tableMap->end()) pre = NULL;
			table = tableMap->find(pre);
			iter = table->second.begin();
		} while (table->second.size() == 1);
	}
	fclose(inputFile); //close file
	fclose(outputFile);
	cout << "normal: " << nFlag << "\tASCII: " << AFlag << endl << endl;
}


int main(void) {
	map<char, pair<int, int>> nTable; //ch, codeword, size
	map<char, map<char, pair<int, int>>> tableMap; //preCh, ch, codeword, size

	readTable(&nTable);
	int EODsize = 0, EODcode = 0;
	EODcode = nTable[0x1A].first;
	EODsize = nTable[0x1A].second;

	readTable(&tableMap, EODsize, EODcode);
	tableMap.insert(make_pair(NULL, nTable));

	writeOutput(trainingHBS, trainingText, &tableMap);
	writeOutput(test1HBS, test1Text, &tableMap);
	writeOutput(test2HBS, test2Text, &tableMap);
	writeOutput(test3HBS, test3Text, &tableMap);
	return 0;
}
