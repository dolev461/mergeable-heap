#pragma once
#include <iostream>

#define MAX_SIZE (256)
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

using namespace std;

struct Node {
    int value;
    Node * left;
    Node * right;
};

class MergeableHeap {
    public:
        MergeableHeap();
        MergeableHeap(int * values, ssize_t length);

        void insert(int value);
        int get_min();

        void print();
    
    private:
        Node * root;

        void min_heapify(int value);

    protected:
        Node _list[MAX_SIZE];
        ssize_t _length;
};