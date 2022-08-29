#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif

template<class T> class Queue
{
public:
    int front;
    int rear;
    int size; //Free to define (recommand 100 or 200)
    T* val;

    Queue() {
        size = 100; //queue size -> 100
        front = 0; rear = 0; // empty
        val = new T[size];
    }
    ~Queue()
    {
        delete[] val;
    }

    void push(T value) {
        // input data
        val[rear++] = value;
        if (rear == size) rear = 0;
    }

    void pop() {
        //Change Front
        if (++front == size) front = 0;
    }

    bool empty() {
        //Check its empty or not
        if (rear == front) return true; // queue is empty
        else return false;  // not empty
    }

    bool isFull() {
        //Check queue is full or not
        if (rear == front + 1) return true; // queue is full
        else return false;  // not full
    }
};
#endif

