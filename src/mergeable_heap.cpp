#include "mergeable_heap.hpp"

MergeableHeap::MergeableHeap() {
    _head = nullptr;
    _tail = nullptr;

    length = 0;
}

MergeableHeap::~MergeableHeap() {
    Node * it = _head;
    Node * next = nullptr;

    while (it != nullptr) {
        next = it->next;
        delete it;
        it = next;
    }
}

void MergeableHeap::insert(int value) {
    Node * tmp = new Node;
    *tmp = {
        .value = value,
        .next = nullptr,
    };

    if (nullptr == _head) {
        _head = tmp;
        _tail = tmp;
    } else {
        _tail->next = tmp;
        _tail = _tail->next;
    }

    length += 1;
}

void MergeableHeap::print() {
    Node * it = _head;

    while (it->next != nullptr) {
        cout << it ->value << " -> ";
        it = it->next;
    }

    cout << it->value << endl;
}