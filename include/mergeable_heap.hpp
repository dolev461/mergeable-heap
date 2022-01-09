#pragma once
#include <iostream>

using namespace std;

enum Mode {
    UNSUPPORTED = -1,
    SORTED,
    UNSORTED,
    FOREIGN,
};

/* Base data structure for mergeable-heap */
struct Node {
    int value;
    Node * next;
    Node * prev;
};

class MergeableHeap {
    public:
        /* Initialize a new MergeableHeap with the required operations mode
        *
        * Arguments:
        *   mode - Operations mode to run MergeableHeap methods
        */
        MergeableHeap(Mode mode);

        /* Destructor to delete all available this instace nodes */
        ~MergeableHeap();

        /* Insert a new node as requried by the mheap mode
        *
        * Arguments:
        *   value - Integer value of the new node
        */
        void insert(int value);

        /* Return the node with the smallest value */
        Node * get_minimum();

        /* Detach and return the node with the smallest value */
        Node * extract_minimum();

        /* Insert all input nodes to this instance to create one merged data
        *
        * Arguments:
        *   mheap - MergeableHeap instance to take nodes from
        *       *be aware that mheap will be empty afterwards
        */
        void merge(MergeableHeap * mheap);

        /* Detach a node from this mergeable-heap by reference
        *
        * Arguments:
        *   node - Node reference to detach
        *       *if the node does exists in this mheap, does nothing
        *       *make sure to delete the node on the outside scope
        */
        void detach(Node * node);

        /* Similar to detach but deleting the node
        *
        * Arguments:
        *   node - Node reference to detach and delete
        */
        void pop(Node * node);

        /* Print all this available nodes */
        void print();

    private:
        /***********************************************************
         * Check attached docs document for algorithms explanation *
         ***********************************************************/

        /* Insert a node sorted from min to max - from head to tail */
        void insert_sorted(Node * node);
        /* Insert a node sorted from min to max - from init_node to tail */
        Node * insert_sorted(Node * node, Node * init_node);
        /* Insert this node as the new tail */
        void insert_unsorted(Node * node);
        /* Insert unsorted without values duplications */
        void insert_foreign(Node * node);
        /* Check if value is exists in this mergeable-heap */
        bool is_exists(int value);

        /* Merge sorted_mheap to this mheap while maintaining sort properties */
        void merge_sorted(MergeableHeap * sorted_mheap);
        /* Attach this tail to unsorted_meap head */
        void merge_unsorted(MergeableHeap * unsorted_mheap);
        /* Merge unsorted without values duplications */
        void merge_foreign(MergeableHeap * unsorted_foreign_mheap);

        Node * _head;
        Node * _tail;
        Mode _mode;
};