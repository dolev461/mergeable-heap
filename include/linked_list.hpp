#include <iostream>

using namespace std;

typedef struct node_s node_t;
struct node_s {
    int value;
    node_t * next;
};

class LinkedList {
    public:
        LinkedList();

        void insert(int value);

        size_t length;

    private:
        node_t * _head;
        node_t * _tail;
};