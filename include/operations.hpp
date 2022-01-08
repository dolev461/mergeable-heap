#pragma once

enum OpId {
    UNKNOWN = -1,
    MAKEHEAP = 0,
    INSERT = 1,
    MINIMUM = 2,
    EXTRACT_MINIMUM = 3,
    EXIT,
};

struct OpInsert {
    OpId id;
    int value;
};

union Operation {
    OpId id;
    /* Space for custom operations which need more values */
    OpInsert insert;
};
