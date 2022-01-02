#pragma once
#include <iostream>
#include <list>
#include <iterator>

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
        void init();

    protected:
        list<Node> _list;
};