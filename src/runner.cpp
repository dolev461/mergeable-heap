#include "runner.hpp"

Runner::Runner() {
}

Runner::Runner(string path) {
    _file.open(path);
}

Mode Runner::select_mode() {
    string mode_str;
    Mode mode;

    cout << ">> Choose mode [sorted/unsorted/foreign]: ";
    getline(cin, mode_str);

    if (mode_str.compare("sorted") == 0) {
        mode = SORTED;
    }
    else if (mode_str.compare("unsorted") == 0) {
        mode = UNSORTED;
    }
    else if (mode_str.compare("foreign") == 0) {
        mode = FOREIGN;
    }
    else {
        mode = UNSUPPORTED;
    }

    return mode;
}

bool Runner::run(list<MergeableHeap> * mheaps, Mode mode) {
    Operation op;
    MergeableHeap * mheap = new MergeableHeap(mode);

    next(&op);
    if (MAKEHEAP != op.id) {
        cout << "[-] The first operation must be MakeHeap!" << endl;
        return false;
    }

    do {
        next(&op);
        switch (op.id)
        {
        case MAKEHEAP:
            // Push the last mergeable-heap and create a new one
            mheaps->push_back(*mheap);
            mheap = new MergeableHeap(mode);
            break;

        case INSERT:
            mheap->insert(op.insert.value);
            mheap->print();
            break;
        
        case MINIMUM:
            cout << "[!] Minimum of last mergeable-heap: " << mheap->get_minimum()->value << endl;
            break;

        case EXTRACT_MINIMUM:
            cout << "[!] Extracted minimum of last mergeable-heap: " << mheap->extract_minimum()->value << endl;
            break;

        case UNION:
            cout << "[!] Merging mergeable-heaps!" << endl;
            mheap->merge(&mheaps->back());
            mheaps->pop_back();
            mheap->print();
            break;

        case EXIT:
            mheaps->push_back(*mheap);
            cout << "[+] Bye bye :)" << endl;
            break;

        default:
            cout << "[-] Unsupported operation - exiting!" << endl;
            break;
        }
    } while (op.id != UNKNOWN && op.id != EXIT);

    mheaps->push_back(*mheap);
    return true;
}

void Runner::next(Operation * op) {
    string op_txt;
    stringstream int_val;
    int num = 0;

    op->id = UNKNOWN;

    if (_file.is_open()) {
        getline(_file, op_txt);
    } else {
        cout << "[+] New operation [MakeHeap/Insert X/Minimum/ExtractMinimum/Union/Exit]:" << endl;
        cout << ">> ";
        getline(cin, op_txt);
    }

    // Erase carriage return from line if exists
    if (op_txt[op_txt.size() - 1] == '\r') {
        op_txt.erase(op_txt.size() - 1);
    }

    if (op_txt.compare("MakeHeap") == 0) {
        // Makeheap command
        op->id = MAKEHEAP;
    }
    else if (op_txt.rfind("Insert", 0) == 0) {
        // Insert command - search for insert value
        op_txt.erase(0, op_txt.find(" ") + 1);
        int_val << op_txt;
        int_val >> num;

        op->insert.id = INSERT;
        op->insert.value = num;
    }
    else if (op_txt.compare("Minimum") == 0) {
        op->id = MINIMUM;
    }
    else if (op_txt.compare("ExtractMinimum") == 0) {
        op->id = EXTRACT_MINIMUM;
    }
    else if (op_txt.compare("Union") == 0) {
        op->id = UNION;
    }
    else if (op_txt.empty()) {
        op->id = EXIT;
    }
}
