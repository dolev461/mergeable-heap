#pragma once

class MergeableHeap {
    public:
        MergeableHeap(int value);
        int get_min();

    private:
        int _head;
};