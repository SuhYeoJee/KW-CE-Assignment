#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include "Result.h"
#include "Graph.h"
#include <fstream>
#include <cstring>


class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    // the filepath for the error log

    // the file stream for the result log
    std::ofstream fout;
    // the file stream for the error log

    // graph instance to manage the vertics.
    Graph m_graph;

    //sort function pointer
    vector<int>(Manager::* sortFunc)(vector<int>) = &Manager::quickSort;

public:
    ~Manager();
    void Run(const char* filepath);
    void PrintError(Result result); 
    

private:
    Result Load(const char* filepath);
    Result Print();
    Result FindPathBfs(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey);
    Result FindShortestPathBellmanFord(int startVertexKey, int endVertexKey);
    Result FindShortestPathFloyd();
    Result RabinKarpCompare(const char* CompareString, const char* ComparedString);
    void UpdateRabinKarp(const char* str1, const char* str2, bool* arr);
    void CompressRabinKarp(vector<int> v);
    char* CompressStr(const char* fullstr, const char* str, int subsize, vector<int> v);

    // return true when str1, str2 has same substr which size int
    bool RabinKarp(const char* str1, const char* str2, int size);
    // return compressed str
    char* RabinKarp(const char* str, int size);
    //return substr pos
    vector<int> RabinKarp(const char* substr, const char* fullstr);

    void setsortFunc(const char* s) {
        if (!strcmp("quick", s)) sortFunc = &Manager::quickSort;
        else if (!strcmp("insert", s)) sortFunc = &Manager::insertSort;
        else if (!strcmp("merge", s)) sortFunc = &Manager::mergeSort;
        else if (!strcmp("heap", s)) sortFunc = &Manager::heapSort;
        else if (!strcmp("bubble", s)) sortFunc = &Manager::bubbleSort;
        else throw InvaildAlgorithmName;
        fout << "Sorted by: " << s << " Sorting" << endl;
    }

    vector<int> insertSort(vector<int>v);
    vector<int> quickSort(vector<int> v);
    void _quickSort(vector <int> * v, const int left, const int right);
    vector<int> bubbleSort(vector<int> v);
    vector<int> heapSort(vector<int> v);
    vector<int> mergeSort(vector<int> v);
    
    void _mergesort(vector <int>* v, const int left, const int right);

    void merge(vector <int>* v, const int left, const int mid, const int right);
};

#endif

