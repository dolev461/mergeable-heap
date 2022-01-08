#pragma once
#include <iostream>

using namespace std;

enum Mode {
    UNSUPPORTED = -1,
    SORTED,
    UNSORTED,
    FOREIGN,
};

struct Node {
    int value;
    Node * next;
    Node * prev;
};

class MergeableHeap {
    public:
        MergeableHeap(Mode mode);
        ~MergeableHeap();

        void insert(int value);
        Node * get_minimum();
        Node * extract_minimum();

        void print();

        size_t size;

    private:
        void insert_sorted(Node * node);
        void insert_unsorted(Node * node);
        void insert_foreign(Node * node);

        Node * _head;
        Node * _tail;
        Mode _mode;
};