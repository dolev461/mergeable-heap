#include "runner.hpp"

Runner::Runner() {
}

Runner::Runner(string path) {
    _file.open(path);
}

void Runner::next(Operation * op) {
    string op_txt;
    stringstream int_val;
    int num = 0;

    op->id = UNKNOWN;

    if (_file.is_open()) {
        getline(_file, op_txt);
    } else {
        getline(cin, op_txt);
    }

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

bool Runner::run(list<MergeableHeap> * heaps, Mode mode) {
    Operation op;
    MergeableHeap * heap = new MergeableHeap(mode);

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
            heap = new MergeableHeap(mode);
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
