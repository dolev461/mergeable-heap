#pragma once
#include <iostream>

#define MAX_SIZE (256)

class MergeableHeap {
    public:
        MergeableHeap(int * values, size_t length);

        int get_min();

    protected:
        int _list[MAX_SIZE];
};