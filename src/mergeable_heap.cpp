#include "mergeable_heap.hpp"

MergeableHeap::MergeableHeap() {
    _length = 0;
}

MergeableHeap::MergeableHeap(int * values, ssize_t length) {
    _length = length;

    // Copy the given list to internal list
    for (int i = 0; i < length; i++) {
        _list[i] = {
            .value = values[i],
            .left = _list + (2 * i) + 1,
            .right = _list + (2 * i) + 2,
        };
    }

    for (int i = length; i < ARRAY_LENGTH(_list); i++) {
        _list[i] = {
            .value = -1,
            .left = nullptr,
            .right = nullptr,
        };
    }

    for (int i = (length / 2) - 1; i >= 0; i--) {
        min_heapify(i);
    }
}

void MergeableHeap::insert(int value) {
    _list[_length].value = value;
    _length++;
}

int MergeableHeap::get_min() {
    return _list[0].value;
}

void MergeableHeap::print() {
    cout << "[";
    for (int i = 0; i < _length - 1; i++) {
        cout << _list[i].value << ", ";
    }

    if (0 <= _length - 1) {
        cout << _list[_length - 1].value;
    }

    cout << "]" << endl;
}

void MergeableHeap::min_heapify(int index) {
    Node * curr = &_list[index];
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