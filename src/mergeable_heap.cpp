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

    size++;
}

void MergeableHeap::insert_sorted(Node * node) {
    Node * it = _head;

    while (it->next != nullptr && it->next->value < node->value) {
        it = it->next;
    }

    if (node->value < it->value) {
        /* If node->value is smaller than it value than it means we need to replace the head */
        node->next = it;
        it->prev = node;
        _head = node;
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
    }
}

void MergeableHeap::insert_unsorted(Node * node) {
    node->prev = _tail;
    _tail->next = node;
    _tail = node;
}

void MergeableHeap::insert_foreign(Node * node) {
    Node * it = _head;

    while (it != nullptr && it->value != node->value) {
        it = it->next;
    }

    if (it == nullptr) {
        insert_unsorted(node);
    }
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

    if (min_node == nullptr) {
        // Empty data
        return nullptr;
    }

    cout << "MIN NODE " << min_node->value << endl;
    if (min_node == _head) {
        cout << "HERE 1" << endl;
        _head = min_node->next;
        _head->prev = nullptr;
    }
    else if (min_node == _tail) {
        cout << "HERE 2" << endl;
        _tail = min_node->prev;
        _tail->next = nullptr;
    } else {
        cout << "HERE 3" << min_node->prev << endl;
        min_node->prev->next = min_node->next;
        cout << "HERE 4" << endl;
        min_node->next->prev = min_node->prev;
    }

    return min_node;
}

void MergeableHeap::print() {
    Node * it = _head;

    while (it->next != nullptr) {
        cout << it ->value << " -> ";
        it = it->next;
    }

    cout << it->value << endl;
}

void MergeableHeap::merge(MergeableHeap * mheap) {
    cout << "MERGING" << endl;
    if (mheap == nullptr || mheap->_head == nullptr) {
        return;
    }

    switch (_mode) {
        case SORTED:
            merge_sorted(mheap);
            break;

        case UNSORTED:
        case FOREIGN:
            cout << "HERE" << endl;
            mheap->_head->prev = _tail;

            _tail->next = mheap->_head;
            _tail = mheap->_tail;

            mheap->_head = _head;
            break;

        default:
            return;
    }
}

void MergeableHeap::merge_sorted(MergeableHeap * sorted_mheap) {

}
