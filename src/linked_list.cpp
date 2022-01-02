#include "linked_list.hpp"

LinkedList::LinkedList() {
    _head = nullptr;
    _tail = nullptr;

    length = 0;
}

void LinkedList::insert(int value) {
    node_t * tmp = new node_t;
    *tmp = {
        .value = -1,
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