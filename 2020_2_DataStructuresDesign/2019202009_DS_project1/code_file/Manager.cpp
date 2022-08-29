#include "Manager.h"

Manager::Manager()
{
    ds_queue = NULL;
    ds_bst = NULL;
    ds_heap = NULL;
}

Manager::~Manager()
{
    //delete
    if (ds_queue) {
        while(!ds_queue->empty()) ds_queue->pop();
    }
    if (ds_bst) delete ds_bst;
    if (ds_heap) delete ds_heap;
}

void Manager::run(char * command)
{
    fin.open(command); //COMMAND FILE
    flog.open("log.txt", ios::app); // LOG FILE
    if(!fin)
    {
        flog << "File Open Error" << endl;
        return;
    }

    char cmd[32];
    
    while (!fin.eof())
    {
        fin.getline(cmd, 32); //read command file
        char tmp[32] = {};
        strcpy(tmp, cmd); //to fine command
        if (strchr(cmd, ' ')) strtok(tmp, " ");
        else if (strlen(cmd) == 0) continue;

        if (strcmp(tmp, "LOAD") == 0) //1. LOAD
        {
            if (LOAD(cmd))
            {
                PrintSuccess((char*)"LOAD");
            }
            else
            {
                PrintErrorCode(100);
            }
        }
        else if (strcmp(tmp, "ADD") == 0){ //2.ADD
            if (!ADD(cmd))
            {
                PrintErrorCode(200);
            }
        }
        else if (strcmp(tmp, "QPOP") == 0) { //3.QPOP
            if (QPOP(cmd))
            {
                PrintSuccess((char*)"QPOP");
            }
            else
            {
                PrintErrorCode(300);
            }
        }
        else if (strcmp(tmp, "SEARCH") == 0) { //4.SEARCH
            if (!SEARCH(cmd))
            {
                PrintErrorCode(400);
            }
        }
        else if (strcmp(tmp, "PRINT") == 0) { //5.PRINT(B/H)
            if (!PRINT(cmd))
            {
                PrintErrorCode(500);
            }
        }
        else if (strcmp(tmp, "BPOP") == 0) { //6.BPOP
            if (BPOP(cmd))
            {
                PrintSuccess((char*)"BPOP");
            }
            else
            {
                PrintErrorCode(600);
            }
        }

        else if(strcmp(tmp, "EXIT") == 0) //7.EXIT
        {
            PrintSuccess((char *)"EXIT");
            break;
        }
        else
        {
            flog << "========== ERROR ==========" << endl;
            flog << "Command Error" << endl;
            flog << "===========================" << endl << endl;
        }
    }
    fin.close();
    flog.close();
}

bool Manager::LOAD(char* cmd)
{
    strtok(cmd, " "); if (strtok(NULL, " ")) return false;//too many Parameters
    if (ds_queue)  return false;  //Queue already exist 
    ds_queue = new queue <PatientNode*>(); //create Patient_Queue
    fdata.open("data.txt"); //Open "data.txt"
    if (!fdata) return false; // No file 

    char data[32], *name,*temp, *cough, *loc;
    try {
        while (!fdata.eof())
        {
            fdata.getline(data, 32); // read data file
            if (strlen(data) == 0) continue;
            name = strtok(data, " "); //get data
            temp = strtok(NULL, " ");
            cough = strtok(NULL, " ");
            loc = strtok(NULL, " ");

            if ((name == NULL) | (temp == NULL) | (cough == NULL) | (loc == NULL)) throw 1; //lack of parameters
            if (strtok(NULL, " ")) throw - 2; //too many Parameters

            PatientNode* patient = new PatientNode(); //new PatientNode
            patient->SetName(name); //insert data
            patient->SetTemp(atof(temp));
            patient->SetCough(cough[0]);
            patient->SetLoc(loc);

            ds_queue->push(patient); //enqueue
        }
    }
    catch (int) { 
        fdata.close(); //close data file
        return false; 
    }
    fdata.close();
    return true;

}

bool Manager::ADD(char * cmd)
{
    char * name, *cough, * loc;
    float temp;
    try {
        strtok(cmd, " "); //get data
        name = strtok(NULL, " "); if (!name) throw -1; //lack of parameters
        temp = atof(strtok(NULL, " ")); if (!temp) throw - 1;
        cough = strtok(NULL, " "); if (!cough) throw - 1;
        loc = strtok(NULL, " "); if (!loc) throw - 1;
        if (strtok(NULL, " ")) throw - 2; //too many Parameters

        PatientNode* patient = new PatientNode(); //new PatientNode
        patient->SetName(name); //insert data
        patient->SetTemp(temp);
        patient->SetCough(cough[0]);
        patient->SetLoc(loc);

        if (!ds_queue) { ds_queue = new queue <PatientNode*>(); } //No Patient queue
        ds_queue->push(patient); //enqueue

        flog << "========== " << "ADD" << " ==========" << endl;
        flog << patient->GetName() << '/' << patient->GetTemp() << '/' <<
            patient->GetCough() << '/' << patient->GetLoc() << endl;
        flog << "============================" << endl << endl;
    }
    catch (int) {return false;}
    return true;
}

bool Manager::QPOP(char* cmd)
{
    try {
        if (!ds_queue) throw -1; //No Patient queue
        strtok(cmd, " ");
        char *tmp = strtok(NULL, " ");
        if (tmp == NULL) throw - 2; //lack of parameter
        else if (ds_queue->size() < atoi(tmp)) throw -3; //larger than ds_queue size
        if (strtok(NULL, " ")) throw - 4; //too many Parameters

        if (!ds_bst) { ds_bst = new LocationBST; } //make L-BST

        for (int i = 0; i < atoi(tmp); i++) {

            PatientNode* PNode = ds_queue->front(); //get PatientNode
            ds_queue->pop();
            LocationNode* LNode = ds_bst->GetRoot(); //to find LocationNode

            while (1) { //find LocationNode
                if (int i = (strcmp(PNode->GetLoc(), LNode->GetLoc()))) {
                    if (i < 0) { LNode = LNode->GetLeft(); }
                    else { LNode = LNode->GetRight(); }
                }
                else break;
            }
            if (!LNode->GetBST()) { // no BST
                PatientBST* BST = new PatientBST(); //make PatientBST
                LNode->SetPatientBST(BST);
            }
            LNode->GetBST()->Insert(PNode);
        }
    }
    catch (int) {return false;}
    return true;
}

bool Manager::SEARCH(char * cmd)
{
    try {
        if (!ds_bst) throw - 1; //No location bst
        strtok(cmd, " ");
        char* name = strtok(NULL, " "); //name to find
        if (name == NULL) throw - 2; //lack of parameter
        if (strtok(NULL, " ")) throw - 3; //too many Parameters

        return ds_bst->Search(name);
    }
    catch (int) { return false; }
}

bool Manager::PRINT(char* cmd)
{
    try {
        strtok(cmd, " ");
        char* tmp = strtok(NULL, " "); //'B' or 'H'
        if (tmp == NULL) throw - 2; //lack of parameter

        if (!strcmp(tmp, "B")) {
            if (!ds_bst) throw - 1; //No location bst
            tmp = strtok(NULL, " "); // (PRE/IN/POST/LEVEL) Traversal 
            if (tmp == NULL) throw - 2; //lack of parameter
            if (strtok(NULL, " ")) throw - 3; //too many Parameters
            flog << "========== " << "PRINT" << " ==========" << endl<<"BST"<<endl;
            if (!strcmp(tmp, "PRE")) {
                ds_bst->Print_PRE(ds_bst->GetRoot());
            }
            else if (!strcmp(tmp, "IN")) {
                ds_bst->Print_IN(ds_bst->GetRoot());
            }
            else if (!strcmp(tmp, "POST")) {
                ds_bst->Print_POST(ds_bst->GetRoot());
            }
            else if (!strcmp(tmp, "LEVEL")) {
                ds_bst->Print_LEVEL();
            }
            flog << "============================" << endl << endl;
        }
        else if (!strcmp(tmp, "H")) {
            if (!ds_heap) throw - 1; //No location heap
            if (strtok(NULL, " ")) throw - 3; //too many Parameters
            flog << "========== " << "PRINT" << " ==========" << endl<<"Heap"<<endl;
            ds_heap->Print();
            flog << "============================" << endl << endl;
        }
        else throw - 3; //parameter error
    }
    catch (int) { return false; }
    return true;
}

bool Manager::BPOP(char* cmd)
{   
    try {
        if (!ds_bst) throw - 1; //No location bst
        strtok(cmd, " ");
        char* name = strtok(NULL, " "); // name to delete
        if (name == NULL) throw - 2; //lack of parameter
        if (strtok(NULL, " ")) throw - 3; //too many Parameters
        if (!ds_heap)
            ds_heap = new LocationHeap; //create Location Heap

        char* Location = ds_bst->Delete(name);
        if (!Location) throw - 3;// location error
        if (!ds_heap->Insert(Location)) throw - 4;
    }
    catch (int) { return false; }
    return true;

}

void Manager::PrintErrorCode(int num)
{
    flog << "========== ERROR ==========" << endl;
    flog << num << endl;
    flog << "===========================" << endl << endl;
}
void Manager::PrintSuccess(char * act)
{
    flog << "========== " << act << " ==========" << endl;
    flog << "Success" << endl;
    flog << "============================" << endl << endl;
}
