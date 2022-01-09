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
        void merge(MergeableHeap * mheap);

        void detach(Node * node);
        void pop(Node * node);
        void print();

        size_t size;

    private:
        void insert_sorted(Node * node);
        Node * insert_sorted(Node * node, Node * init_node);

        void insert_unsorted(Node * node);

        void insert_foreign(Node * node);
        bool is_exists(int value);

        void merge_sorted(MergeableHeap * sorted_mheap);
        void merge_unsorted(MergeableHeap * unsorted_mheap);
        void merge_foreign(MergeableHeap * unsorted_foreign_mheap);

        Node * _head;
        Node * _tail;
        Mode _mode;
};