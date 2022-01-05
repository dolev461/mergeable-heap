#include "mergeable_heap.hpp"

MergeableHeap::MergeableHeap(Mode mode) {
    size = 0;

    _head = nullptr;
    _tail = nullptr;
    _mode = mode;
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
    Node * node = new Node;
    *node = {
        .value = value,
        .next = nullptr,
    };

    if (nullptr == _head) {
        _head = node;
        _tail = node;
    } else {
        switch (_mode) {
            case SORTED:
                insert_sorted(node);
                break;

            case UNSORTED:
                insert_unsorted(node);
                break;

            case FOREIGN:
                insert_foreign(node);
                break;
        }
    }

    size++;
}

void MergeableHeap::insert_sorted(Node * node) {
    Node * it = _head;

    while (it != nullptr && it->value < node->value) {
        it = it->next;
    }

    if (it == _head) {
        node->next = it;
        _head = node;
    }
    else if (it != nullptr) {
        node->next = it->next;
        it->next = node;
        if (_tail == it) {
            _tail = node;
        }
    } else {
        _tail->next = node;
        _tail = node;
    }
}

void MergeableHeap::insert_unsorted(Node * node) {
    _tail->next = node;
    _tail = node;
}

void MergeableHeap::insert_foreign(Node * node) {

}

void MergeableHeap::print() {
    Node * it = _head;

    while (it->next != nullptr) {
        cout << it ->value << " -> ";
        it = it->next;
    }

    cout << it->value << endl;
}