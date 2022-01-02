#include "mergeable_heap.hpp"

MergeableHeap::MergeableHeap() {
}

MergeableHeap::MergeableHeap(int * values, ssize_t length) {
    Node * ileft = nullptr;
    Node * iright = nullptr;

    // Copy the given list to internal list
    for (int i = 0; i < length; i++) {
        insert(values[i]);
    }

    /*
    for (int i = (length / 2) - 1; i >= 0; i--) {
        min_heapify(i);
    }
    */
}

void MergeableHeap::insert(int value) {
    size_t list_size;
    int parent_index;
    Node * node;
    list<Node>::iterator it = _list.begin();

    if (it == _list.end()) {
        _list.push_back({
            .value=value,
            .left=nullptr,
            .right=nullptr
        });
        return;
    }

    node = &_list.front();
    _list.push_back({
        .value=node->value,
        .left=nullptr,
        .right=nullptr,
    });

    node->value = value;

    list_size = _list.size();
    parent_index = (list_size / 2) - 1;
    for (int i = 0; i < parent_index; i++) {
        it++;
    }
    if (list_size % 2 == 0) {
        it->left = &_list.back();
    } else {
        it->right = &_list.back();
    }

    /*
    _list[_length - 1].value = _list[0].value;
    _list[0].value = value;

    for (int i = (_length / 2) - 1; i >= 0; i--) {
        min_heapify(i);
    }*/
}

int MergeableHeap::get_min() {
    return _list.begin()->value;
}

void MergeableHeap::print() {
    cout << "[";
    for (auto it : _list) {
        cout << it.value << ", ";
    }

    cout << "]" << endl;
}

void MergeableHeap::min_heapify(int index) {
    list<Node>::iterator it = _list.begin();
    advance(it, index);

    Node * curr = &(*it);
    Node * left = nullptr;
    Node * right = nullptr;
    Node * min = nullptr;

    while (-1 != curr->left->value) {
        left = curr->left;
        right = curr->right;

        if (left->value < curr->value) {
            min = left;
        } else {
            min = curr;
        }

        if (-1 != right->value && right->value < min->value) {
            min = right;
        }

        if (min != curr) {
            // Replace node value with smaller node child (curr->value <-> left->value)
            curr->value += min->value;
            min->value = curr->value - min->value;
            curr->value -= min->value;

            curr = min;
        } else {
            break;
        }
    }
}