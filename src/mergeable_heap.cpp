#include "mergeable_heap.hpp"

MergeableHeap::MergeableHeap(Mode mode) {
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
        .prev = nullptr,
    };

    if (_head == nullptr) {
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
}

void MergeableHeap::insert_sorted(Node * node) {
    insert_sorted(node, _head);
}

Node * MergeableHeap::insert_sorted(Node * node, Node * init_node) {
    Node * it = init_node;

    while (it->next != nullptr && it->next->value < node->value) {
        it = it->next;
    }

    if (node->value < it->value) {
        node->next = it;
        node->prev = it->prev;
        it->prev = node;
        if (_head == it) {
            _head = node;
        }
    }
    else {
        if (it->next != nullptr) {
            it->next->prev = node;
        }

        node->next = it->next;
        node->prev = it;
        it->next = node;
        if (_tail == it) {
            _tail = node;
        }

        /* Return the last ordered node */
        it = node;
    }

    return it;
}

void MergeableHeap::insert_unsorted(Node * node) {
    node->prev = _tail;
    _tail->next = node;
    _tail = node;
}

void MergeableHeap::insert_foreign(Node * node) {
    if (!is_exists(node->value)) {
        insert_unsorted(node);
    } else {
        cout << "[-] Value " <<  node->value << " already exists - skipping" << endl;
    }
}

bool MergeableHeap::is_exists(int value) {
    Node * it = _head;

    while (it != nullptr && it->value != value) {
        it = it->next;
    }

    return it != nullptr;
}

Node * MergeableHeap::get_minimum() {
    Node * min_node;
    Node * it;

    switch (_mode) {
        case SORTED:
            min_node = _head;
            break;

        case UNSORTED:
        case FOREIGN:
            min_node = _head;
            it = _head;
            while (it != nullptr) {
                if (it->value < min_node->value) {
                    min_node = it;
                }

                it = it->next;
            }
            break;

        default:
            min_node = nullptr;
            break;
    }

    return min_node;
}

Node * MergeableHeap::extract_minimum() {
    Node * min_node = get_minimum();

    detach(min_node);

    return min_node;
}

void MergeableHeap::merge(MergeableHeap * mheap) {
    if (mheap == nullptr || mheap->_head == nullptr) {
        /* No nodes to merge */
        return;
    }

    switch (_mode) {
        case SORTED:
            merge_sorted(mheap);
            break;

        case UNSORTED:
            merge_unsorted(mheap);
            break;

        case FOREIGN:
            merge_foreign(mheap);
            break;

        default:
            return;
    }

    /* Take ownership over the nodes */
    mheap->_head = nullptr;
    mheap->_tail = nullptr;
}

void MergeableHeap::merge_sorted(MergeableHeap * sorted_mheap) {
    Node * this_it = _head;
    Node * other_it = sorted_mheap->_head;
    Node * other_next;

    while (this_it != nullptr && other_it != nullptr) {
        other_next = other_it->next;

        /* Detach the inserted node from sorted_mheap */
        this_it = insert_sorted(other_it, this_it);
        other_it = other_next;
    }
}

void MergeableHeap::merge_unsorted(MergeableHeap * unsorted_mheap) {
    /* Connect the other head to this tail */
    unsorted_mheap->_head->prev = _tail;

    /* Connect this tail to the other mheap */
    _tail->next = unsorted_mheap->_head;
    _tail = unsorted_mheap->_tail;
}

void MergeableHeap::merge_foreign(MergeableHeap * unsorted_foreign_mheap) {
    Node * it = unsorted_foreign_mheap->_head;
    Node * next = nullptr;

    while (it != nullptr) {
        next = it->next;

        if (is_exists(it->value)) {
            cout << "[-] Value " <<  it->value << " already exists - popping" << endl;
            unsorted_foreign_mheap->pop(it);
        }

        it = next;
    }

    merge_unsorted(unsorted_foreign_mheap);
}

void MergeableHeap::detach(Node * node) {
    if (node == nullptr) {
        return;
    }

    if (_head == node) {
        _head = node->next;
        _head->prev = nullptr;
    }
    else if (_tail == node) {
        _tail = node->prev;
        _tail->next = nullptr;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    /* Transfer of ownership */
    node->next = nullptr;
    node->prev = nullptr;
}

void MergeableHeap::pop(Node * node) {
    detach(node);
    delete node;
}

void MergeableHeap::print() {
    Node * it = _head;

    while (it != nullptr) {
        cout << it ->value << " -> ";
        it = it->next;
    }

    cout << endl;
}
