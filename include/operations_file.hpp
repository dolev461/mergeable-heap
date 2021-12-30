#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

typedef enum op_e {
    UNKNOWN = -1,
    MAKE_HEAP = 0,
    INSERT = 1,
} op_id_t;

typedef struct operation {
    op_id_t id;
    int extra;
} op_t;

class OperationsFile {
    public:
        OperationsFile(string path);

        void next(op_t * op);
        void print();

    protected:
        ifstream _file;
};