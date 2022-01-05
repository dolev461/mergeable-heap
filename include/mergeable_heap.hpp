#pragma once
#include <iostream>

using namespace std;

enum Mode {
    SORTED,
    UNSORTED,
    FOREIGN,
};

struct Node {
    int value;
    Node * next;
};

class MergeableHeap {
    public:
        MergeableHeap(Mode mode);
        ~MergeableHeap();

        void insert(int value);
        void print();

        size_t size;

    private:
        void insert_sorted(Node * node);
        void insert_unsorted(Node * node);
        void insert_foreign(Node * node);

    protected:
        Node * _head;
        Node * _tail;
        Mode _mode;
};