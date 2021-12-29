#include "mergeable_heap.hpp"

MergeableHeap::MergeableHeap(int value) {
    _head = value;
}

MergeableHeap::get_min() {
    return _head;
}