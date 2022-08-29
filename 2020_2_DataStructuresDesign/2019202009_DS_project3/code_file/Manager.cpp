#include "Manager.h"
#include <cstring>
#include <math.h>
#include "MinHeap.h"

Manager::~Manager()
{
	if (fout.is_open())
		fout.close();
}

void Manager::Run(const char* filepath)
{
	std::ifstream fin;
	fin.open(filepath); //command file
	fout.open(RESULT_LOG_PATH);
	if (!fin) {
		PrintError(CommandFileNotExist);
		return;
	}
	while (!fin.eof()) {
		try {
			char cmd[50], * op = NULL, * temp = NULL;
			fin.getline(cmd, 50); //read command file
			if (temp = strstr(cmd, "//")) { *temp = NULL; } //ignore comment
			op = strtok_r(cmd, " ", &temp); //get opcode
			if (strlen(cmd) == 0) continue; //empty line

			if (!strcmp(op, "LOAD")) {
				fout << "===== LOAD =====" << endl;
				//parameter: 1 (txt file)
				if (!*temp) throw InvaildParameter; // no parameter
				char* datafile;
				datafile = strtok_r(temp, " ", &temp);
				if (*temp) throw InvaildParameter; //too many parameter

				PrintError(Load(datafile));
			}
			else if (!strcmp(op, "UPDATE")) {
				fout << "===== UPDATE =====" << endl;
				//parameter: 0
				if (*temp) throw InvaildParameter; //too many parameter
				if (!m_graph.Size()) throw GraphNotExist;
				for (int i = 0; i < m_graph.Size(); i++) {
					for (int j = i + 1; j < m_graph.Size(); j++) {
						RabinKarpCompare(m_graph.getNameArry()[i], m_graph.getNameArry()[j]);
					}
				}
				fout << "Success" << endl;
				throw Success; // print result
			}
			else if (!strcmp(op, "PRINT")) {
				fout << "===== PRINT =====" << endl;
				//parameter: 0
				if (*temp) throw InvaildParameter; //too many parameter
				PrintError(Print());
			}
			else if (!strcmp(op, "BFS")) {
				fout << "===== BFS =====" << endl;
				//parameter: 2 (start, end vertex)
				if (!*temp) throw InvaildParameter; // no parameter
				int s, e;
				s = atoi(strtok_r(temp, " ", &temp));
				if (!*temp) throw InvaildParameter; // no parameter
				e = atoi(strtok_r(temp, " ", &temp));
				if (*temp) throw InvaildParameter; //too many parameter

				PrintError(FindPathBfs(s, e));
			}
			else if (!strcmp(op, "DIJKSTRA")) {
				fout << "===== DIJKSTRA =====" << endl;
				//parameter: 2 (start, end vertex)
				if (!*temp) throw InvaildParameter; // no parameter
				int s, e;
				s = atoi(strtok_r(temp, " ", &temp));
				if (!*temp) throw InvaildParameter; // no parameter
				e = atoi(strtok_r(temp, " ", &temp));
				if (*temp) throw InvaildParameter; //too many parameter

				PrintError(FindShortestPathDijkstraUsingSet(s, e));
			}
			else if (!strcmp(op, "DIJKSTRAMIN")) {
				fout << "===== DIJKSTRAMIN =====" << endl;
				//parameter: 2 (start, end vertex)
				if (!*temp) throw InvaildParameter; // no parameter
				int s, e;
				s = atoi(strtok_r(temp, " ", &temp));
				if (!*temp) throw InvaildParameter; // no parameter
				e = atoi(strtok_r(temp, " ", &temp));
				if (*temp) throw InvaildParameter; //too many parameter

				PrintError(FindShortestPathDijkstraUsingMinHeap(s, e));
			}
			else if (!strcmp(op, "BELLMANFORD")) {
				fout << "===== BELLMANFORD =====" << endl;
				//parameter: 2 (start, end vertex)
				if (!*temp) throw InvaildParameter; // no parameter
				int s, e;
				s = atoi(strtok_r(temp, " ", &temp));
				if (!*temp) throw InvaildParameter; // no parameter
				e = atoi(strtok_r(temp, " ", &temp));
				if (*temp) throw InvaildParameter; //too many parameter

				PrintError(FindShortestPathBellmanFord(s, e));
			}
			else if (!strcmp(op, "FLOYD")) {
				fout << "===== FLOYD =====" << endl;
				//parameter: 0
				if (*temp) throw InvaildParameter; //too many parameter
				PrintError(FindShortestPathFloyd());
			}
			else if (!strcmp(op, "CONFIG")) {
				fout << "===== CONFIG LOG=====" << endl;
				//parameter: 2 (-sort, algorithm)
				if (!*temp) throw InvaildParameter; // no parameter
				op = strtok_r(temp, " ", &temp);
				if (!*temp) throw InvaildParameter; // no parameter
				if (strcmp(op, "-sort")) throw InvalidOptionName;
				op = strtok_r(temp, " ", &temp);
				if (*temp) throw InvaildParameter; //too many parameter
				setsortFunc(op);
				PrintError(Success);
			}
			else { //op error
				fout << "=====" << op << "=====" << endl;
				throw NonDefinedCommand;
			}
		}
		catch (Result r) {
			PrintError(r);
		}
	}
}
void Manager::PrintError(Result result)
{
	//fout<<"errorName"<<endl;

	switch (result)
	{
	case Success:
		//fout << "Success" << endl;
		break;
	case InvaildAlgorithmName:
		fout << "InvaildAlgorithmName" << endl;
		break;
	case InvalidOptionName:
		fout << "InvalidOptionName" << endl;
		break;
	case FaildtoUpdatePath:
		fout << "FaildtoUpdatePath" << endl;
		break;
	case InvaildParameter:
		fout << "InvaildParameter" << endl;
		break;
	case CommandFileNotExist:
		fout << "=====SYSTEM=====" << endl;
		fout << "CommandFileNotExist" << endl;
		break;
	case LoadFileNotExist:
		fout << "LoadFileNotExist" << endl;
		break;
	case VertexKeyNotExist:fout << "VertexKeyNotExist" << endl;
		break;
	case InvalidVertexKey:fout << "InvalidVertexKey" << endl;
		break;
	case GraphNotExist:fout << "GraphNotExist" << endl;
		break;
	case InvalidAlgorithm:fout << "InvalidAlgorithm" << endl;
		break;
	case NegativeCycleDetected:fout << "NegativeCycleDetected" << endl;
		break;
	case IsolatedVertex:fout << "IsolatedVertex" << endl;
		break;
	case NonDefinedCommand:fout << "NonDefinedCommand" << endl;
		break;
	default:
		break;
	}


	fout << "===============" << endl << endl;
	//ferr << "Error code: " << result << std::endl;
	fout << "===============" << endl;
	fout << "Error code: " << result << endl;
	fout << "===============" << endl << endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
	m_graph.makeGraph(filepath);  //make graph
	if (m_graph.Size()) {
		fout << "Success" << endl;
		return Success; // print result
	}
	else return LoadFileNotExist;
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
	if (!m_graph.Size()) return GraphNotExist; //no graph
	m_graph.Print(fout);  //print graph
	return Success;
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with BFS (stack and queue)
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindPathBfs(int startVertexKey, int endVertexKey)
{
	if (!m_graph.Size()) return GraphNotExist; //no graph
	vector<int> v;
	v = m_graph.FindPathBfs(startVertexKey, endVertexKey);  //BFS
	int length = 0;

	//print shortest path
	fout << "shortest path: ";
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << ' ';
		if (i > 0) length++; //ignore weight
	} fout << endl;

	///sort
	v = (this->*sortFunc)(v);

	//print sorted nodes
	fout << "sorted nodes: ";
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << ' ';
	} fout << endl;

	fout << "path length: " << length << endl; //print length

	CompressRabinKarp(v); // print course

	return Success; //print result

}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	if (!m_graph.Size()) return GraphNotExist; //no graph
	vector<int> v;
	v = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);  //dijkstra(set)
	int length = 0;

	//print shortest path
	fout << "shortest path: ";
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << ' ';
		if (i > 0) {
			Edge* eTemp = m_graph.FindVertex(v[i - 1])->GetHeadOfEdge();
			for (int j = 0; j < v[i]; j++) {
				eTemp = eTemp->GetNext();
			}
			length += eTemp->GetWeight();
		}
	} fout << endl;
	
	//////////sort
	v = (this->*sortFunc)(v);

	//print sorted nodes
	fout << "sorted nodes: ";
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << ' ';
	} fout << endl;

	fout << "path length: " << length << endl; //print length

	CompressRabinKarp(v); // print course

	return Success; //print result
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	if (!m_graph.Size()) return GraphNotExist; //no graph
	vector<int> v;
	v = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);  //dijkstra(minheap)
	int length = 0;

	//print shortest path
	fout << "shortest path: ";
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << ' ';
		if (i > 0) {
			Edge* eTemp = m_graph.FindVertex(v[i - 1])->GetHeadOfEdge();
			for (int j = 0; j < v[i]; j++) {
				eTemp = eTemp->GetNext();
			}
			length += eTemp->GetWeight();
		}
	} fout << endl;

	//sort
	v = (this->*sortFunc)(v);
	//print sorted nodes
	fout << "sorted nodes: ";
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << ' ';
	} fout << endl;

	fout << "path length: " << length << endl; //print length

	CompressRabinKarp(v); // print course

	return Success; //print result
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	if (!m_graph.Size()) return GraphNotExist; //no graph
	vector<int> v;
	v = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);  //bellmanford
	int length = 0;

	//print shortest path
	fout << "shortest path: ";
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << ' ';
		if (i > 0) {
			Edge* eTemp = m_graph.FindVertex(v[i - 1])->GetHeadOfEdge();
			for (int j = 0; j < v[i]; j++) {
				eTemp = eTemp->GetNext();
			}
			length += eTemp->GetWeight();
		}
	} fout << endl;


	/////////////////////////// v sort
	v = (this->*sortFunc)(v);

	//print sorted nodes
	fout << "sorted nodes: ";
	for (int i = 0; i < v.size(); i++) {
		fout << v[i] << ' ';
	} fout << endl;

	fout << "path length: " << length << endl; //print length

	CompressRabinKarp(v); // print course

	return Success; //print result
}

Result Manager::FindShortestPathFloyd() {
	if (!m_graph.Size()) return GraphNotExist; //no graph
	vector<vector<int>> vv;
	vv = m_graph.FindShortestPathFloyd();  //bellmanford

	//print
	for (int i = 0; i < vv.size(); i++) {
		for (int j = 0; j < vv[i].size(); j++)
			fout << vv[i][j] << ' ';
		fout << endl;
	}fout << endl;
	return Success; // print result
}

Result Manager::RabinKarpCompare(const char* CompareString, const char* ComparedString)
{
	bool arr[3];
	UpdateRabinKarp(CompareString, ComparedString, arr);

	int key1 = NULL, key2 = NULL; //find vertex key
	for (int i = 0; i < m_graph.Size(); i++) {
		if (!strcmp(CompareString, m_graph.getNameArry()[i])) key1 = i;
		else if (!strcmp(ComparedString, m_graph.getNameArry()[i])) key2 = i;
	}
	if ((key1 == m_graph.Size()) || (key2 == m_graph.Size()))
		throw FaildtoUpdatePath; //no such name

	if (arr[0] == true) { //rule 1
		m_graph.UpdateEdge(key1, key2, 0.9); // 10% down
		m_graph.UpdateEdge(key2, key1, 0.9); // 10% down
	}
	if (arr[1] == true) { //rule 2
		m_graph.UpdateEdge(key1, key2, 0.9); // 10% down
		m_graph.UpdateEdge(key2, key1, 0.9); // 10% down
	}
	if (arr[2] == true) { //rule 3
		m_graph.UpdateEdge(key1, key2, 0.8); // 20% down
		m_graph.UpdateEdge(key2, key1, 0.8); // 20% down
	}
	return Success;
}

void Manager::UpdateRabinKarp(const char* str1, const char* str2, bool* arr) {
	char* name1 = NULL, * name2 = NULL, * temp1 = NULL, * temp2 = NULL;
	char fullName1[70], fullName2[70];
	strcpy(fullName1, str1);
	strcpy(fullName2, str2);

	name1 = strtok_r(fullName1, "'", &temp1); //get name1 <-str1
	name2 = strtok_r(fullName2, "'", &temp2); //get name2 <-str2
	arr[0] = RabinKarp(name1, name2, 5);//rule1: 10% down
	arr[1] = RabinKarp(name1, name2, 10);  //rule2: 10% down

	strtok_r(temp1, " ", &temp1); //get temp1 <- after ('s)
	strtok_r(temp2, " ", &temp2); //get temp2 <- after ('s)
	name1 = strtok_r(temp1, " ", &temp1); //one word
	while (name1) {
		if (arr[2] = RabinKarp(name1, temp2, strlen(name1)))  //rule3: 20% down
			break;
		name1 = strtok_r(temp1, " ", &temp1); //next word
	}
}

void Manager::CompressRabinKarp(vector<int> v) {
	char str[140] = "";

	for (int i = 0; i < v.size(); i++) { //string to compress
		strcat(str, m_graph.getNameArry()[v[i]]);
	}
	int size = strlen(str);
	char* comstr = NULL, fullstr[140];
	strcpy(fullstr, str);
	while (size>0) {
		if (comstr = RabinKarp(fullstr, size)) {
			break;
		}
		else size--;
	}
	fout << "Course: " << comstr << endl;

	return;
}

bool Manager::RabinKarp(const char* str1, const char* str2, int size) {
	char* temp1 = NULL, * temp2 = NULL;
	if ((strlen(str1) >= size) || (strlen(str2) >= size)) {
		int hash1 = 0, hash2 = 0, temp1 = 0, temp2 = 0;
		for (int k = 0; k < size; k++) {
			//get first hash1 <= str1[0~size-1]
			temp1 <<= 1;
			if ((str1[k] > 96) && (str1[k] < 123)) //small letter
				temp1 += (str1[k] - 32);
			else temp1 += str1[k];
			//get first hash2 <= str2[0~size-1]
			temp2 <<= 1;
			if ((str2[k] > 96) && (str2[k] < 123)) //small letter
				temp2 += (str2[k] - 32);
			else temp2 += str2[k];
		}
		for (int i = 0; str1[i + size - 1] != NULL; i++) {
			//get hash1
			if (i == 0) hash1 = temp1;
			else { //next hash1 <= str1[i~i+size-1]
				if ((str1[i - 1] > 96) && (str1[i - 1] < 123))//small letter
					hash1 -= ((str1[i - 1] - 32) << (size - 1));
				else hash1 -= (str1[i - 1] << (size - 1));
				hash1 <<= 1;
				if ((str1[i + size - 1] > 96) && (str1[i + size - 1] < 123))//small letter
					hash1 += (str1[i + size - 1] - 32);
				else hash1 += str1[i + size - 1];
			}
			for (int j = 0; str2[j + size - 1] != NULL; j++) {
				//get hash2
				if (j == 0) hash2 = temp2;
				else { //next hash2 <= str2[i~i+size-1]
					if ((str2[j - 1] > 96) && (str2[j - 1] < 123)) //small letter
						hash2 -= ((str2[j - 1] - 32) << (size - 1));
					else hash2 -= (str2[j - 1] << (size - 1));
					hash2 <<= 1;
					if ((str2[j + size - 1] > 96) && (str2[j + size - 1] < 123)) //small letter
						hash2 += (str2[j + size - 1] - 32);
					else hash2 += str2[j + size - 1];
				}
				if (hash1 == hash2) return true; //CMP hash
			}
		}
	}
	return false; //(too short to cmp) or (not found)
}

char* Manager::RabinKarp(const char* str, int size) {
	char* sTemp;
	int subHash = 0, fullHash = 0, fTemp = 0,  count = 0;
	int start = 0;
	sTemp = new char[size+1];
	vector <int> v; // '*' compress point

	for (int i = 0; i < size; i++) {
		fTemp <<= 1; //get fullstring hash
		if ((str[i] > 96) && (str[i] < 123)) fTemp += (str[i] - 32); //smaller letter
		else fTemp += str[i];
	}
	while(true){
		subHash = 0; 
		//v.clear();
		while (!v.empty()) v.pop_back();
		for (int i = 0; i < size; i++) { // substr, hash
			sTemp[i] = str[start + i];	//get substr: str[start : start + size -1]
			if (sTemp[i] == NULL) { //no same part
				delete[] sTemp;
				return NULL;
			}
			subHash <<= 1; //get substr hash
			if ((sTemp[i] > 96) && (sTemp[i] < 123)) 
				subHash += (sTemp[i] - 32); //smaller letter
			else subHash += sTemp[i];
		}sTemp[size] = NULL;

		for (int i = 0;str[i + size -1]!=NULL;i++) {
			//get fullstr hash
			if (i == 0) fullHash = fTemp;
			else {
				if ((str[i - 1] > 96) && (str[i - 1] < 123))//small letter
					fullHash -= ((str[i - 1] - 32) << (size - 1));
				else fullHash -= (str[i - 1] << (size - 1));
				fullHash <<= 1;
				if ((str[i + size - 1] > 96) && (str[i + size - 1] < 123))//small letter
					fullHash += (str[i + size - 1] - 32);
				else fullHash += str[i + size - 1];
			}
			if (subHash == fullHash) {
				v.push_back(i);
				for (int k = 1; k < size-1; k++) { // to prevent 'aaaaaa' <= 'aaa'aaa/ a'aaa'aa ,,,
					i++;
					if (str[i - 1] == NULL) return NULL;
					if ((str[i - 1] > 96) && (str[i - 1] < 123))//small letter
						fullHash -= ((str[i - 1] - 32) << (size - 1));
					else fullHash -= (str[i - 1] << (size - 1));
					fullHash <<= 1;
					if ((str[i + size - 1] > 96) && (str[i + size - 1] < 123))//small letter
						fullHash += (str[i + size - 1] - 32);
					else fullHash += str[i + size - 1];
				}

			}
			if (v.size() == 2) {
				return CompressStr(str, sTemp, size, v); //substring found -> compress
			}
		}
		start++; // to next substr
	}
}

char* Manager::CompressStr(const char* fullstr, const char* substr, int subsize, vector<int> v) {
	char* comstr, fTemp[150];
	comstr = new char[150];

	//rule 2
	strcpy(fTemp, fullstr); //full string
	strcpy(comstr, substr); //insert substring
	comstr[subsize] = '*'; //insert '*'
	comstr[subsize + 1] = NULL;
	
	int pos = NULL; 
	for (int i = 0; i < v.size(); i++) {
		pos = v[i];// substring start pos 
		for (int j = 0; j < subsize; j++) {
			fTemp[pos + j] = NULL; // compressed substring
		}
	}

	//rule 3 - delete shop, class, academy (write once)
	v = RabinKarp("shop", fullstr); int size = strlen("shop");
	if (!v.empty()) {
		for (int i = 0; i < v.size(); i++) { //delete shop
			if (i == 0) continue;
			pos = v[i];// substring start pos 
			for (int j = 0; j < size; j++) {
				fTemp[pos + j] = NULL; // compressed substring
			}
		}
	}
	v = RabinKarp("class", fullstr); size = strlen("class");
	if (!v.empty()) {
		for (int i = 0; i < v.size(); i++) { //delete shop
			if ((RabinKarp("class", comstr)).size() == 0) { //substr not have "class"
				if (i == 0) continue;
			}
			pos = v[i];// substring start pos 
			for (int j = 0; j < size; j++) {
				fTemp[pos + j] = NULL; // compressed substring
			}
		}
	}
	v = RabinKarp("academy", fullstr); size = strlen("academy");
	if (!v.empty()) {
		for (int i = 0; i < v.size(); i++) { //delete shop
			if (i == 0) continue;
			pos = v[i];// substring start pos 
			for (int j = 0; j < size; j++) {
				fTemp[pos + j] = NULL; // compressed substring
			}
		}
	}

	int k = subsize + 1;
	for (int i = 0; i < strlen(fullstr); i++) { // insert other string
		if (fTemp[i]) comstr[k++] = fTemp[i];
	}comstr[k] = NULL; //end of string

	return (char*)comstr;
}

vector<int> Manager::RabinKarp(const char* substr, const char* fullstr) {
	vector <int> v;
	int size = strlen(substr);
	if (strlen(fullstr) >= strlen(substr)) {
		int subHash = 0, fullHash = 0;
		for (int k = 0; k < size; k++) {
			//get first substr <= str1[0~size-1]
			subHash <<= 1;
			if ((substr[k] > 96) && (substr[k] < 123)) //small letter
				subHash += (substr[k] - 32);
			else subHash += substr[k];
			//get first fullstr <= str2[0~size-1]
			fullHash <<= 1;
			if ((fullstr[k] > 96) && (fullstr[k] < 123)) //small letter
				fullHash += (fullstr[k] - 32);
			else fullHash += fullstr[k];
		}
		for (int i = 0; fullstr[i + size - 1] != NULL; i++) {
			//get fullHash
			if (i == 0);
			else { //next hash1 <= str1[i~i+size-1]
				if ((fullstr[i - 1] > 96) && (fullstr[i - 1] < 123))//small letter
					fullHash -= ((fullstr[i - 1] - 32) << (size - 1));
				else fullHash -= (fullstr[i - 1] << (size - 1));
				fullHash <<= 1;
				if ((fullstr[i + size - 1] > 96) && (fullstr[i + size - 1] < 123))//small letter
					fullHash += (fullstr[i + size - 1] - 32);
				else fullHash += fullstr[i + size - 1];
			}
			if (fullHash == subHash) {
				v.push_back(i);
			}
		}
	}
	return v;
}

vector<int> Manager::insertSort(vector<int> v) {
	int temp = 0;
	int  j;
	for (int i = 1; i < v.size(); i++) {
		temp = v[i];
		for (j = i-1 ; j >= 0; j--) { //j: pos to insert temp
			if (v[j] < temp) break;
			v[j + 1] = v[j];
		}
		v[j+1] = temp;
	}
	return v;
}

vector<int> Manager::quickSort(vector<int> v) {
	_quickSort(&v, 0, v.size() - 1);
	return v;
}
void Manager::_quickSort(vector <int> * v, const int left, const int right) {
	if (left >= right)return;
	int i = left + 1, j = right, pivot = (*v)[left], temp = 0;
	while (i <= j) {
		if ((*v)[i] < pivot) i++; //already sorted
		if ((*v)[j] > pivot) j--;
		if (i < j) { // i,j swap
			temp = (*v)[i];
			(*v)[i++] = (*v)[j];
			(*v)[j++] = temp;
		}
		else if (i > j) { // temp, j swap
			temp = (*v)[left];
			(*v)[left] = (*v)[j];
			(*v)[j] = temp;
		}
	}
	_quickSort(v, left, j - 1); //recursive call
	_quickSort(v, j + 1, right);
}

vector<int> Manager::bubbleSort(vector<int> v) {
	int temp = 0;
	for (int i = v.size()-1; i >0; i--) {
		for (int j = 0; j < i; j++) {
			if (v[j] > v[j + 1]) { //cmp next node
				temp = v[j + 1]; //swap
				v[j + 1] = v[j];
				v[j] = temp;
			}
		}
	}
	return v;
}

vector<int> Manager::heapSort(vector<int> v) {
	MinHeap<int, int> mh;
	for (int i = 0; i < v.size(); i++) { //make minheap
		mh.Push(v[i],v[i]);
	}
	for (int i = 0; i < v.size(); i++) {
		v[i] = mh.Top().first;
		mh.Pop();
	}
	return v;
}

vector<int> Manager::mergeSort(vector<int> v) {
	_mergesort(&v, 0, v.size()-1);
	return v;
}

void Manager::_mergesort(vector <int>* v,const int left, const int right) {
	if (left >= right) return;
	int mid = (left + right) / 2;
	_mergesort(v, left, mid); _mergesort(v, mid + 1, right);
	merge(v, left, mid, right);
}

void Manager::merge(vector <int>* v, const int left, const int mid, const int right ) {
	int* sorted = new int[(*v).size()];
	int i = left, j = mid + 1, k = left;

	while ((i <= mid) && (j <= right)) {
		if ((*v)[i] <= (*v)[j]) sorted[k++] = (*v)[i++];
		else sorted[k++] = (*v)[j++];
	}

	if (i > mid) {
		for (int p = j; p <= right; p++) {
			sorted[k++] = (*v)[p];
		}
	}
	else {
		for (int p = i; p <= mid; p++) {
			sorted[k++] = (*v)[p];
		}
	}

	for (int i = left; i <= right; i++) {
		(*v)[i] = sorted[i];
	}

}

