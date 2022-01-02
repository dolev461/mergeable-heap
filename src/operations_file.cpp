#include "operations_file.hpp"

OperationsFile::OperationsFile(string path) {
    _file.open(path);
}

void OperationsFile::next(op_t * op) {
    string op_txt;
    stringstream int_val;
    int num = 0;

    op->id = UNKNOWN;

    getline(_file, op_txt);

    // Erase carriage return from line if exists
    if (op_txt[op_txt.size() - 1] == '\r') {
        op_txt.erase(op_txt.size() - 1);
    }

    if (op_txt.compare("MakeHeap") == 0) {
        // Makeheap command
        op->makeheap.id = MAKEHEAP;
    } else if (op_txt.rfind("Insert", 0) == 0) {
        // Insert command - search for insert value
        op_txt.erase(0, op_txt.find(" ") + 1);
        int_val << op_txt;
        int_val >> num;

        op->insert.id = INSERT;
        op->insert.value = num;
    } 
}

void OperationsFile::print() {
    op_t op;
    
    do {
        next(&op);
        cout << op.id << endl;
    } while (op.id != UNKNOWN);
}

bool OperationsFile::run(list<MergeableHeap> * heaps) {
    op_t op;
    MergeableHeap * heap = new MergeableHeap();

    next(&op);
    if (MAKEHEAP != op.id) {
        // Operations file must start with MakeHeap
        return false;
    }

    cout << "Make heap" << endl;

    do {
        next(&op);
        switch (op.id)
        {
        case MAKEHEAP:
            cout << "\nMake heap" << endl;
            // Push the last heap and create a new one
            heaps->push_back(*heap);
            heap = new MergeableHeap();
            break;

        case INSERT:
            cout << "Insert " << op.insert.value << endl;
            heap->insert(op.insert.value);
            break;
        
        default:
            cout << "\nEND\n" << endl;
            break;
        }
    } while (op.id != UNKNOWN);

    heaps->push_back(*heap);
    return true;
}
