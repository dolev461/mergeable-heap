#include "operations_file.hpp"

OperationsFile::OperationsFile(string path) {
    _file.open(path);
}

void OperationsFile::next(op_t * op) {
    string op_txt;
    op->id = UNKNOWN;
    op->extra = -1;

    getline(_file, op_txt);

    // Erase carriage return from line if exists
    if (op_txt[op_txt.size() - 1] == '\r') {
        op_txt.erase(op_txt.size() - 1);
    }

    if (op_txt.compare("MakeHeap") == 0) {
        op->id = MAKE_HEAP;
    } else if (op_txt.rfind("Insert", 0) == 0) {
        // Starts with "Insert"
        op->id = INSERT;
        op_txt.erase(0, op_txt.find(" ") + 1);
        stringstream intval(op_txt);
        int num = 0;
        intval >> num;
        op->extra = num;
    } 
}

void OperationsFile::print() {
    op_t op;
    
    do {
        next(&op);
        cout << op.id << " " << op.extra << endl;
    } while (op.id != UNKNOWN);
}
