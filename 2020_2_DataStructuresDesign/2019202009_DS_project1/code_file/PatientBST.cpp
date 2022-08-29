#include "PatientBST.h"

PatientBST::PatientBST()
{
    Root = NULL;
}

PatientBST::~PatientBST()
{   // use LEVEL Traversal
    queue <PatientBSTNode*>* que = new queue <PatientBSTNode*>;
    PatientBSTNode* tmp = Root;
    que->push(tmp);
    while (!que->empty()) {
        tmp = que->front();
        que->pop(); //delete at queue
        if (tmp->GetLeft())
            que->push(tmp->GetLeft());
        if (tmp->GetRight())
            que->push(tmp->GetRight());
        delete tmp; //delete node
    }
    delete que;
}

PatientBSTNode * PatientBST::GetRoot()
{
    return Root;
}

bool PatientBST::Insert(PatientNode * node)
{
    //QPOP
    PatientBSTNode* PBNode = new PatientBSTNode(node); //new PatientBSTNode

    if (!Root) { //first node
        Root = PBNode;
        return true;
    }

    PatientBSTNode* tmp = Root;
    while (1) {
        int i = strcmp(tmp->GetName(), PBNode->GetName());
        if (i> 0) { //Left child
            if (tmp->GetLeft()) //exist
                tmp = tmp->GetLeft();
            else {
                tmp->SetLeft(PBNode);
                break;
            }
        }
        else if (i < 0) { //Right child
            if (tmp->GetRight()) //exist
                tmp = tmp->GetRight();
            else {
                tmp->SetRight(PBNode);
                break;
            }
        }
        else return false; //same name
    }
    return true;
}

bool PatientBST::Search(char * name, PatientBSTNode* node)
{
    //SEARCH

    if (node != NULL) {
        if (!strcmp(node->GetName(), name)) {
            ofstream flog;
            flog.open("log.txt", ios::app);
            flog << "========== " << "SEARCH" << " ==========" << endl;
            flog << node->GetName() << '/' << node->GetDisease() << endl;
            flog << "============================" << endl << endl;
            flog.close();
            return true;
        }
        if(Search(name, node->GetLeft())) return true;
        if(Search(name, node->GetRight())) return true;
    }
    return false;
}

bool PatientBST::Delete(char * name, PatientBSTNode* node)
{
    //BPOP
    PatientBSTNode* tmp, * pre;
    tmp = Root; pre = Root;
    int i;
    while (1) {
        if (tmp == NULL) return false;
        i = strcmp(tmp->GetName(), name);
        if (i == 0) { //delete tmp
            if ((tmp->GetLeft() != NULL) && (tmp->GetRight() != NULL)) { //two child

                PatientBSTNode* rep, * prer; //find replace node
                rep = tmp->GetLeft(); prer = tmp;
                while (1) {
                    if (!rep->GetRight()) { // replace node
                        if (rep->GetLeft()) {
                            prer->SetRight(rep->GetLeft()); // Left child replace rep
                            rep->SetLeft(NULL);
                        }
                        else  // rep has no child
                            prer->SetRight(NULL);
                        break;
                    }
                    else {
                        prer = rep;
                        rep = rep->GetRight();
                    }
                }
                if (tmp == pre) Root = rep; //tmp is root node
                else if (pre->GetLeft()) {
                    if (strcmp(pre->GetLeft()->GetName(), name) == 0)  //left child is tmp
                        pre->SetLeft(rep);
                    else
                        pre->SetRight(rep); //right chile is tmp
                }     
                else pre->SetRight(rep);//right child is tmp
                rep->SetLeft(tmp->GetLeft());
                rep->SetRight(tmp->GetRight());
                delete tmp;
            }
            else if ((tmp->GetLeft() == NULL) && (tmp->GetRight() == NULL)) { //no child
                if (pre == tmp) //delete Root Node
                    Root = NULL;
                else if (pre->GetLeft()) {
                    if (strcmp(pre->GetLeft()->GetName(), name) == 0)  //left child is tmp
                        pre->SetLeft(NULL);
                    else
                        pre->SetRight(NULL); //right chile is tmp
                }
                else
                    pre->SetRight(NULL); //right chile is tmp

                delete tmp;
            }
            else { //one child
                if (tmp == pre) { //tmp is root node
                    if (tmp->GetLeft())  //left child replace
                        Root = tmp->GetLeft();
                    else //right child replace
                        Root = tmp->GetRight();
                }
                else if (pre->GetLeft())  //left child is tmp
                    pre->SetLeft(NULL);
                else //right child is tmp
                    pre->SetRight(NULL);
                delete tmp;
            }
            return true;
        }
        else if(i > 0) {
            pre = tmp;
            tmp = tmp->GetLeft();
        }
        else {
            pre = tmp;
            tmp = tmp->GetRight();
        }
    }
}

void PatientBST::Print_PRE(PatientBSTNode * node)
{
    //PRINT B PRE

    if (node != NULL) {
        flogPRINT(node); //PRE order Traversal
        Print_PRE(node->GetLeft());
        Print_PRE(node->GetRight());
    }
    return;
}
void PatientBST::Print_IN(PatientBSTNode * node)
{
    //PRINT B IN

    if (node != NULL) {
        Print_IN(node->GetLeft()); //IN order Traversal
        flogPRINT(node);
        Print_IN(node->GetRight());
    }
    return;
}
void PatientBST::Print_POST(PatientBSTNode * node)
{
    //PRINT B POST

    if (node != NULL) {
        Print_POST(node->GetLeft()); //POST order Traversal
        Print_POST(node->GetRight());
        flogPRINT(node);
    }
    return;
}
void PatientBST::Print_LEVEL()
{
    //PRINT B LEVEL
    queue <PatientBSTNode*>* que = new queue <PatientBSTNode*>; //LEVEL Traversal
    PatientBSTNode* tmp = Root;
    que->push(tmp);
    while (!que->empty()){
        tmp = que->front();
        que->pop();
        if(tmp->GetLeft())
            que->push(tmp->GetLeft());
        if (tmp->GetRight())
            que->push(tmp->GetRight());
        flogPRINT(tmp);
    } 
    delete que;
}

void PatientBST ::flogPRINT(PatientBSTNode* node) {
    ofstream flog;
    flog.open("log.txt", ios::app); //print at log file
    flog << node->GetName()<<'/'<<node->GetDisease() << endl;
    flog.close();
}