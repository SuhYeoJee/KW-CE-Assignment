#include "LocationHeap.h"

LocationHeap::LocationHeap()
{
    Heap = new LocationHeapNode *[8];
    size = 0;
}

LocationHeap::~LocationHeap()
{
    delete[] Heap;
}

bool LocationHeap::Insert(char * location)
{
    //BPOP
    int i;
    for (i = 1; i <= size; i++) {
        if (!strcmp(Heap[i]->GetLoc(), location)) { //find Location Heap Node
            Heap[i]->SetCount(1); // count +1
            
            //sort
            while (1) {
                int j = i / 2;
                if (j == 0) return true;
                if (Heap[j]->GetCount() < Heap[i]->GetCount()) { //use Heap[0]: temp
                    Heap[0] = Heap[j];
                    Heap[j] = Heap[i];
                    Heap[i] = Heap[0];
                }
                else return true;
                i = j;
            }
        }
    }

    //new Location Heap Node
    Heap[i] = new LocationHeapNode();
    Heap[i]->SetLoc(location);
    Heap[i]->SetCount(1);
    size++;

    //sort
    while (1) {
        int j = i / 2;
        if (j == 0) return true;
        if (Heap[j]->GetCount() < Heap[i]->GetCount()) {
            Heap[0] = Heap[j];
            Heap[j] = Heap[i];
            Heap[i] = Heap[0];
        }
        else return true;
    }
    return false;
}

void LocationHeap::Print()
{
    //PRINT H
    ofstream flog;
    flog.open("log.txt", ios::app); //open log file
    for (int i = 1; i <= size; i++) {
        flog << Heap[i]->GetCount() <<'/'<< Heap[i]->GetLoc() << endl;
    }
    flog.close(); //close log file
}