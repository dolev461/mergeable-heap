#include "mergeable_heap.hpp"

MergeableHeap::MergeableHeap(int * values, size_t length) {
    for (int i = 0; i < length; i++) {
        _list[i] = values[i];
    }
}

int MergeableHeap::get_min() {
    return _list[0];
}