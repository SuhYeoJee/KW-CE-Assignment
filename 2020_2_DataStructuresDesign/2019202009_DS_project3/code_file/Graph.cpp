#include "Graph.h"
#include "MinHeap.h"
#include <set>
#include "Queue.h"
#include "Result.h"
#include <vector>
#include <cstring>
#include <math.h>


#define BFS_FIRST_PATH

Graph::Graph() // data) Denny's Bread/ 0 6 13 0 0 1
{
	m_pVHead = NULL; m_vSize = NULL;
}
Graph::~Graph()
{
    // TODO: implement
	Clear();
}

void Graph::makeGraph(const char* filepath) // data) Denny's Bread/ 0 6 13 0 0 1
{
	fdata.open(filepath);
	if (!fdata) return; //no txt file

	char line[100], * temp = NULL;
	fdata.getline(line, 10); //read data file
	if (!line) throw - 1; // `error

	int i = atoi(line); //number of store
	nameArry = new char* [i];

	for (int j = 0; j < i; j++) {
		nameArry[j] = new char[70]; //Max name length: 49
		AddVertex(j); //insert vertex
		fdata.getline(line, 100); //read data file
		strcpy(nameArry[j],  strtok_r(line, "/", &temp));
		for (int k = 0; k < i; k++) //insert edge
			AddEdge(j, k, atoi(strtok_r(temp, " ", &temp)));
	}
}

void Graph::AddVertex(int vertexKey) {
	Vertex* temp = new Vertex(vertexKey);
	Vertex* pre = m_pVHead;
	while (pre!=NULL) { //insert at last
		if (pre->GetNext()) pre = pre->GetNext();
		else {
			pre->SetNext(temp);
			m_vSize++;
			return;
		}
	}
	m_pVHead=temp; // temp is first element
	m_vSize++;
}

void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight) {
	Vertex* vTemp = FindVertex(startVertexKey);
	if (vTemp) { //insert Edge
		vTemp->AddEdge(endVertexKey, weight);
	}
	else { //new vertex
		AddVertex(startVertexKey);
		FindVertex(startVertexKey)->AddEdge(endVertexKey, weight);
	}
}

void Graph::UpdateEdge(int startVertexKey, int endVertexKey, float value) {
	Vertex* vTemp;
	Edge* preEdge = NULL, *eTemp, *updateEdge;
	int updateWeight;

	vTemp = FindVertex(startVertexKey);
	if(!vTemp) throw  FaildtoUpdatePath;
	eTemp = vTemp->GetHeadOfEdge();
	if (!eTemp) throw  FaildtoUpdatePath;

	for (int i = 0; i < endVertexKey; i++) {
		preEdge = eTemp;
		eTemp = eTemp->GetNext();
	}
	updateWeight = ceil(eTemp->GetWeight() * value);
	updateEdge = new Edge(endVertexKey, updateWeight); //new Edge
	updateEdge->SetNext(eTemp->GetNext()); // connect with next edge
	if (!preEdge) // connect with pre edge
		vTemp->SetHeadOfEdge(updateEdge); // update first edge
	else 
		preEdge->SetNext(updateEdge);
	delete eTemp;
}

Vertex* Graph::FindVertex(int key) {
	Vertex* pre = m_pVHead;
	while (pre) { //find vertex
		if (pre->GetKey() == key) return pre; //key found
		else if (pre->GetNext()) pre = pre->GetNext(); //next element
		else break; //no such key
	}
	return NULL;
}

int Graph::Size() const {
	return m_vSize;
}

void Graph::Clear() {
	Vertex* pre = m_pVHead, * temp = NULL;
	while (pre) {
		if (pre->GetNext())temp = pre->GetNext(); //next exist
		else temp = NULL;
		delete pre; //delete
		pre = temp; //to next node
	}
}

void Graph::Print(std::ofstream& fout) {
	Vertex* vTemp = m_pVHead; //first vertex
	Edge* eTemp = NULL;
	while (vTemp) {
		eTemp = vTemp->GetHeadOfEdge(); //first edge
		while (eTemp) {
			fout << eTemp->GetWeight() << ' '; //print data
			eTemp = eTemp->GetNext(); //next edge
		}
		fout << endl;
		vTemp = vTemp->GetNext(); //next vertex
	}
}

bool Graph::IsNegativeEdge() {
	Vertex* vTemp = m_pVHead; //first vertex
	Edge* eTemp = NULL;
	while (vTemp) {
		eTemp = vTemp->GetHeadOfEdge(); //first edge
		while (eTemp) {
			if (eTemp->GetWeight() < 0) return true; // negative edge exist
			eTemp = eTemp->GetNext(); //next edge
		}
		vTemp = vTemp->GetNext(); //next vertex
	}
	return false;
}

std::vector<int> Graph::FindPathBfs(int startVertexKey, int endVertexKey) {
	// ignore weight
	if ((startVertexKey < 0) || (startVertexKey >= m_vSize) ||
		(endVertexKey < 0) || (endVertexKey >= m_vSize)) 
		throw VertexKeyNotExist; //no start or end vertex
	if (IsNegativeEdge()) throw InvalidAlgorithm; //negative edge

	int* IsVisited = new int[m_vSize]; //to check visit, length
	int* parent = new int[m_vSize]; //to find path

	for (int i = 0; i < m_vSize; i++) {//init
		IsVisited[i] = -1; parent[i] = -1; 
	}

	Queue <int>  q;
	q.push(startVertexKey); // enqueue start vertex
	IsVisited[startVertexKey] = 0;
	Vertex* vTemp = FindVertex(startVertexKey);
	while (!q.empty()) { // get spanning tree
		Edge* eTemp = vTemp->GetHeadOfEdge();
		while (eTemp) { // for vTemp's every edge
			if ((eTemp->GetWeight() != 0) && (IsVisited[eTemp->GetKey()] == -1)) { // to visit
				q.push(eTemp->GetKey()); //enqueue
				IsVisited[eTemp->GetKey()] = IsVisited[vTemp->GetKey()] + 1; // update
				parent[eTemp->GetKey()] = vTemp->GetKey();
			}
			eTemp = eTemp->GetNext();
		}
		q.pop(); //dequeue
		vTemp = FindVertex(q.front);
	}

	int length = IsVisited[endVertexKey]; //length of (start~end)
	int iTemp = endVertexKey; //vertex number
	if (IsVisited[endVertexKey] == -1) throw IsolatedVertex; //empty vector

	vector <int> v; //get path
	while (v.size()<=length) {
		v.insert(v.begin(), iTemp);
		iTemp = parent[iTemp];
	}
	delete[] IsVisited;
	delete[] parent;
	return v;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey) {
	if ((startVertexKey < 0) || (startVertexKey >= m_vSize) ||
		(endVertexKey < 0) || (endVertexKey >= m_vSize))
		throw VertexKeyNotExist; //no start or end vertex
	if (IsNegativeEdge()) throw InvalidAlgorithm;
	bool* IsVisited = new bool[m_vSize]; //is visited?
	int* dist = new int[m_vSize]; //distance
	int* parent = new int[m_vSize]; //to find path
	for (int i = 0; i < m_vSize; i++) { //init
		IsVisited[i] = unvisited;
		dist[i] = IN_FINITY;
		parent[i] = -1;
	}

	set <pair<int, int>> s;
	int verA = startVertexKey;
	dist[verA] = 0;
	s.insert(make_pair(0,verA)); //self
	
	while (!s.empty()) { // verA to next
		verA = s.begin()->second; //visit closest node
		IsVisited[verA] = visited;
		s.erase(s.begin()); //delete at set
		Edge* eTemp = FindVertex(verA)->GetHeadOfEdge();
		while (eTemp) {
			if ((eTemp->GetWeight() != 0) &&  //edge exist
				(dist[verA] + (eTemp->GetWeight()) < dist[eTemp->GetKey()]) && //A->next is closer
				(IsVisited[eTemp->GetKey()] == unvisited)) { // unvisited node
				dist[eTemp->GetKey()] = dist[verA] + (eTemp->GetWeight());
				s.insert(make_pair(dist[eTemp->GetKey()], eTemp->GetKey()));
				parent[eTemp->GetKey()] = verA;
			}
			eTemp = eTemp->GetNext();
		}
	}

	int iTemp = endVertexKey; //vertex number

	vector <int> v; //get path
	while (iTemp!=-1) {
		v.insert(v.begin(), iTemp);
		iTemp = parent[iTemp];
	}
	delete[] IsVisited;
	delete[] parent;
	delete[] dist;
	return v;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey) {
	if ((startVertexKey < 0) || (startVertexKey >= m_vSize) ||
		(endVertexKey < 0) || (endVertexKey >= m_vSize))
		throw VertexKeyNotExist; //no start or end vertex
	if (IsNegativeEdge()) throw InvalidAlgorithm; //negative edge
	bool* IsVisited = new bool[m_vSize]; //is visited?
	int* dist = new int[m_vSize]; //distance
	int* parent = new int[m_vSize]; //to find path
	for (int i = 0; i < m_vSize; i++) { //init
		IsVisited[i] = unvisited;
		dist[i] = IN_FINITY;
		parent[i] = -1;
	}

	MinHeap<int, int> mh;
	int verA = startVertexKey;
	dist[verA] = 0; //self
	mh.Push(0, verA); //self

	while (!mh.IsEmpty()) { // verA to next
		verA = mh.Top().second;//visit closest node
		IsVisited[verA] = visited;
		mh.Pop();//delete at set
		Edge* eTemp = FindVertex(verA)->GetHeadOfEdge();
		while (eTemp) {
			if ((eTemp->GetWeight() != 0) &&  //edge exist
				(dist[verA] + (eTemp->GetWeight()) < dist[eTemp->GetKey()]) && //A->next is closer
				(IsVisited[eTemp->GetKey()] == unvisited)) { // unvisited node
				dist[eTemp->GetKey()] = dist[verA] + (eTemp->GetWeight());
				mh.Push(dist[eTemp->GetKey()], eTemp->GetKey());
				parent[eTemp->GetKey()] = verA;
			}
			eTemp = eTemp->GetNext();
		}
	}

	int iTemp = endVertexKey; //vertex number

	vector <int> v; //get path
	while (iTemp != -1) {
		v.insert(v.begin(), iTemp);
		iTemp = parent[iTemp];
	}
	delete[] IsVisited;
	delete[] parent;
	delete[] dist;
	return v;
}

std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey) {
	if ((startVertexKey < 0) || (startVertexKey >= m_vSize) ||
		(endVertexKey < 0) || (endVertexKey >= m_vSize))
		throw VertexKeyNotExist; //no start or end vertex
	int* dist = new int[m_vSize]; //distance
	int* parent = new int[m_vSize]; //to find path
	for (int i = 0; i < m_vSize; i++) { //init
		dist[i] = IN_FINITY;
		parent[i] = -1;
	}
	dist[startVertexKey] = 0; //self

	Vertex* vTemp = FindVertex(startVertexKey); 
	Edge* eTemp = NULL;
	for(int i=0;i<m_vSize;i++) {
		eTemp = vTemp->GetHeadOfEdge(); //first edge
		while (eTemp) {
			if ((eTemp->GetWeight() != 0) &&  //edge exist
				(dist[vTemp->GetKey()] + (eTemp->GetWeight()) < dist[eTemp->GetKey()])) {//A->next is closer
				dist[eTemp->GetKey()] = dist[vTemp->GetKey()] + eTemp->GetWeight();
				parent[eTemp->GetKey()] = vTemp->GetKey();
			}
			eTemp = eTemp->GetNext(); //next edge
		}
		vTemp = vTemp->GetNext(); //next vertex
		if (vTemp == NULL) vTemp = m_pVHead;
	}
	vTemp = FindVertex(startVertexKey);
	eTemp = NULL;
	for (int i = 0; i < m_vSize; i++) {
		eTemp = vTemp->GetHeadOfEdge(); //first edge
		while (eTemp) {
			if ((eTemp->GetWeight() != 0) &&  //edge exist
				(dist[vTemp->GetKey()] + (eTemp->GetWeight()) < dist[eTemp->GetKey()])) {//A->next is closer
				throw NegativeCycleDetected;
			}
			eTemp = eTemp->GetNext(); //next edge
		}
		vTemp = vTemp->GetNext(); //next vertex
		if (vTemp == NULL) vTemp = m_pVHead;
	}

	int iTemp = endVertexKey; //vertex number
	vector <int> v; //get path
	while (iTemp != -1) {
		v.insert(v.begin(), iTemp);
		iTemp = parent[iTemp];
	}
	delete[] parent;
	delete[] dist;
	return v;
}

std::vector<vector<int>> Graph::FindShortestPathFloyd() {
	//copy dist to vv
	vector<vector<int>> dist; //get path
	vector <int> v; //get path
	Vertex* vTemp = m_pVHead;
	Edge* eTemp = NULL;
	for (int i = 0; i < m_vSize; i++) { //copy graph to dist
		eTemp = vTemp->GetHeadOfEdge();
		for (int j = 0; j < m_vSize; j++){
			if (eTemp->GetWeight())
				v.push_back(eTemp->GetWeight());
			else if (eTemp->GetKey() == vTemp->GetKey()) //self
				v.insert(v.end(), 0);//v.push_back(0); 
			else v.push_back(IN_FINITY); //no edge
			eTemp = eTemp->GetNext();
		}
		dist.push_back(v);
		v.clear();
		vTemp = vTemp->GetNext();
	}
	for (int k = 0; k < m_vSize; k++){
		for (int i = 0; i < m_vSize; i++){
			for (int j = 0; j < m_vSize; j++){
				if (dist[i][k] + dist[k][j] < dist[i][j]) // i-k-j is shoter than i-j
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}


	
	for (int k = 0; k < m_vSize; k++) { // check nagative cycle
		for (int i = 0; i < m_vSize; i++) {
			for (int j = 0; j < m_vSize; j++) {
				if (dist[i][k] + dist[k][j] < dist[i][j]) // i-k-j is shoter than i-j
					throw NegativeCycleDetected;
			}
		}
	}

	return dist;
}

