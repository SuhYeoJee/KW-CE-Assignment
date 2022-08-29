#include "LocationBST.h"

LocationBST::LocationBST()
{
    Insert_Location(Root);
}
LocationBST::~LocationBST()
{
    //use LEVEL Traversal
    queue <LocationNode*>* que = new queue <LocationNode*>;
    LocationNode* tmp = Root;
    que->push(tmp);
    while (!que->empty()) {
        tmp = que->front();
        que->pop();
        if (tmp->GetLeft())
            que->push(tmp->GetLeft());
        if (tmp->GetRight())
            que->push(tmp->GetRight());
        delete tmp; // free memory
    }
    while (!que->empty()) que->pop();
    delete que;
}

LocationNode * LocationBST::GetRoot()
{
    return Root;
}

void LocationBST::Insert_Location(LocationNode * node)
{
    //Build once in Constructor
    LocationNode* arr[7];
    char* loc[7] = { (char*)"Gwangju", (char*)"Daegu", (char*)"Seoul",
        (char*)"Busan", (char*)"Daejeon", (char*)"Incheon", (char*)"Ulsan" }; //location data

    int n = 0;
    for (int i = 0; i < 7; i++) { //make Location BST
        arr[i] = new LocationNode;
        arr[i]->SetLoc(loc[i]);
        if (i == 0) continue; //root node
        else if (!arr[n]->GetLeft()) { arr[n]->SetLeft(arr[i]); }
        else { arr[n++]->SetRight(arr[i]); }
    }
    Root = arr[0];
    return;
}

bool LocationBST::Insert_Patient(PatientNode * node)
{
    //QPOP

    queue <LocationNode*>* que = new queue <LocationNode*>; //use LEVEL Traversal
    LocationNode* tmp = Root;
    que->push(tmp);
    while (!que->empty()) {
        tmp = que->front();
        if (tmp->GetBST()) {
            if (tmp->GetBST()->Insert(node)) //insert at PatientBST
                return true;
        }
        que->pop();
        if (tmp->GetLeft())
            que->push(tmp->GetLeft());
        if (tmp->GetRight())
            que->push(tmp->GetRight());
    }
    delete que;
    return false;

}

bool LocationBST::Search(char * name)
{
    //SEARCH

    queue <LocationNode*>* que = new queue <LocationNode*>; //use LEVEL Traversal
    LocationNode* tmp = Root;
    que->push(tmp);
    while (!que->empty()) {
        tmp = que->front();
        if (tmp->GetBST()){
            if(tmp->GetBST()->Search(name, tmp->GetBST()->GetRoot())) //search name at PatientBST
                return true;
        }
        que->pop();
        if (tmp->GetLeft())
            que->push(tmp->GetLeft());
        if (tmp->GetRight())
            que->push(tmp->GetRight());
    }
    delete que;
    return false;
}

char * LocationBST::Delete(char * name)
{
    //BPOP
    queue <LocationNode*>* que = new queue <LocationNode*>; //use LEVEL Traversal
    LocationNode* tmp = Root;
    que->push(tmp);
    while (!que->empty()) {
        tmp = que->front();
        if (tmp->GetBST()) {
            if (tmp->GetBST()->Delete(name, tmp->GetBST()->GetRoot())) //delete node
                return tmp->GetLoc();
        }
        que->pop();
        if (tmp->GetLeft())
            que->push(tmp->GetLeft());
        if (tmp->GetRight())
            que->push(tmp->GetRight());
    }
    while (!que->empty()) que->pop();
    delete que;
    return NULL;
}

void LocationBST::Print_PRE(LocationNode *node)
{
    //PRINT B PRE

    if (node != NULL) {
        if (node->GetBST()) 
            node->GetBST()->Print_PRE(node->GetBST()->GetRoot());
        Print_PRE(node->GetLeft());
        Print_PRE(node->GetRight());
    }
    return;
}
void LocationBST::Print_IN(LocationNode* node)
{
    //PRINT B IN

    if (node != NULL) {
        Print_IN(node->GetLeft());
        if (node->GetBST()) 
            node->GetBST()->Print_IN(node->GetBST()->GetRoot());
        Print_IN(node->GetRight());
    }
    return;
}
void LocationBST::Print_POST(LocationNode* node)
{
    //PRINT B POST

    if (node != NULL) {
        Print_POST(node->GetLeft());
        Print_POST(node->GetRight());
        if (node->GetBST()) 
            node->GetBST()->Print_POST(node->GetBST()->GetRoot());
    }
    return;
}
void LocationBST::Print_LEVEL()
{
    //PRINT B LEVEL
    queue <LocationNode*>* que = new queue <LocationNode*>;
    LocationNode* tmp = Root;
    que->push(tmp);
    while (!que->empty()) {
        tmp = que->front();
        que->pop(); //dequeue
        if (tmp->GetLeft())
            que->push(tmp->GetLeft()); //enqueue
        if (tmp->GetRight())
            que->push(tmp->GetRight()); //enqueue
        if (tmp->GetBST())
            tmp->GetBST()->Print_LEVEL();
    }
    while (!que->empty()) que->pop();
    delete que;
}
