#pragma once

enum OpId {
    UNKNOWN = -1,
    MAKEHEAP = 0,
    INSERT = 1,
};

struct OpMakeHeap {
    OpId id;
};

struct OpInsert {
    OpId id;
    int value;
};

union Operation {
    OpId id;
    OpMakeHeap makeheap;
    OpInsert insert;
};
