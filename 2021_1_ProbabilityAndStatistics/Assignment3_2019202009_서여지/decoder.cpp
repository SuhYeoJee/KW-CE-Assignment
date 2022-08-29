#include <iostream>
#include <string>
#include <map>
using namespace std;

#define inputHBSFile "huffman_code.hbs"
#define tableHBSFile "huffman_table.hbs"
#define outputTextFile "output.txt"

// table.hbs -> table map
void readTable(map<int, pair<char, int>> *table) {
	FILE* tableFile = NULL;
	if (fopen_s(&tableFile, tableHBSFile, "rb")) { //open table
		cout << "ERROR: no [" << tableHBSFile << "] file" << endl;
		exit(-1);
	}
	else {
		char ch = NULL;
		char bitSize = 0;
		unsigned int codeword = 0;
		unsigned long long int buf = 0; //(8byte)
		int count = 0;

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

			table->insert(make_pair(codeword, make_pair(ch, bitSize)));
		}
		fclose(tableFile); //close file
		return;	//EOF
	}
}

// table map -> output.txt
void writeOutput(map<int, pair<char, int>>* table) {
	FILE* inputFile = NULL;
	if (fopen_s(&inputFile, inputHBSFile, "rb")) { //open file
		cout << "ERROR: no [" << inputHBSFile << "] file" << endl;
		exit(-1);
	}
	FILE* outputFile = NULL;
	if (fopen_s(&outputFile, outputTextFile, "wt")) { //make file
		cout << "ERROR: can't make [" << outputTextFile << "] file" << endl;
		exit(-1);
	}
	char ch = NULL;
	unsigned char tmp = 0; //(4byte)
	unsigned long long int buf = 0; //(8byte)
	int count = 0, size=0;
	unsigned int mask = 0xFFFFFFFF;
	map<int, pair<char, int>>::iterator iter;
	while (1){
		while (count < 16) {
			buf <<= 8;
			fread_s(&tmp, sizeof(tmp), 1, 1, inputFile);
			buf += tmp;
			count += 8;
		}
		mask = 0xFFFFFFFF;
		mask >>= (32 - ++size);		//1, 2, 3,,,
		mask &= buf >> (count - size);
		iter = table->find(mask);
		if (iter == table->end()) continue;
		else if (iter->second.second != size) continue;
		else if (iter->second.first == 0x1A) break; //EOF
		fputc(iter->second.first, outputFile);
		count -= size;
		size = 0;
	}
	fclose(inputFile); //close file
	fclose(outputFile);
}

int main(void) {
	map<int, pair<char, int>> table;

	readTable(&table);
	writeOutput(&table);
	return 0;
}