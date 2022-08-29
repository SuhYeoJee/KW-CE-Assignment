#include "Vertex.h"

Vertex::Vertex() {
	m_key = NULL;
	m_size = NULL;
	m_pEHead = NULL;
	m_pNext = NULL;
}

Vertex::Vertex(int key) {
	m_key = key;
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
}

Vertex::~Vertex() {
	Clear();
}

void Vertex::SetNext(Vertex* pNext) {
	m_pNext = pNext;
}

int Vertex::GetKey() const {
	return m_key;
}

Vertex* Vertex::GetNext() const {
	return m_pNext;
}

int Vertex::Size() const {
	return m_size;
}

void Vertex::AddEdge(int edgeKey, int weight) {
	Edge* temp = new Edge(edgeKey, weight); // edge to insert
	Edge* pre = m_pEHead;
	while(pre) { //insert at last
		if (pre->GetNext()) pre = pre->GetNext();
		else {
			pre->SetNext(temp);
			m_size++;
			return;
		}
	}
	m_pEHead=temp; // temp is first element
	m_size++;
}

Edge* Vertex::GetHeadOfEdge() const {
	return m_pEHead;
}

void Vertex::Clear() {
	Edge* pre = m_pEHead, *temp=NULL;
	while (pre) {
		if (pre->GetNext()) temp = pre->GetNext(); //next exist
		else temp = NULL;
		delete pre; //delete
		pre = temp; //to next node
	}
}

void Vertex::SetHeadOfEdge(Edge* pHead) {
	m_pEHead = pHead;
}
