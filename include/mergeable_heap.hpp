#pragma once
#include <iostream>

using namespace std;

struct Node {
    int value;
    Node * next;
};

class MergeableHeap {
    public:
        MergeableHeap();
        ~MergeableHeap();

        void insert(int value);
        void print();

        size_t size;

    private:
        Node * _head;
        Node * _tail;
};