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

bool Runner::run(list<MergeableHeap*> * mheaps, Mode mode) {
    Operation op = {UNKNOWN};
    MergeableHeap * mheap = nullptr;
    MergeableHeap * last = nullptr;

    next(&op);
    if (MAKEHEAP != op.id) {
        cout << "[-] The first operation must be MakeHeap!" << endl;
        return false;
    }

    do {
        switch (op.id)
        {
        case MAKEHEAP:
            cout << "[!] Creating a new mergeable-heap" << endl;
            mheap = new MergeableHeap(mode);
            mheaps->push_back(mheap);
            break;

        case INSERT:
            mheap->insert(op.insert.value);
            mheap->print();
            break;
        
        case MINIMUM:
            cout << "[!] Minimum: " << mheap->get_minimum()->value << endl;
            break;

        case EXTRACT_MINIMUM:
            cout << "[!] Extracted minimum: " << mheap->extract_minimum()->value << endl;
            break;

        case UNION:
            if (mheaps->size() < 2) {
                cout << "[-] There is no mergeable-heaps to merge" << endl;
                break;
            }

            cout << "[!] Merging mergeable-heaps!" << endl;
            /* Pop the current mergeable-heap */

            mheaps->pop_back();
            last = mheaps->back();

            last->merge(mheap);

            delete mheap;
            mheap = last;

            /* Destroy the element */
            //mheaps->pop_back();
            //delete last;
            mheap->print();
            break;

        case EXIT:
            cout << "[+] Bye bye :)" << endl;
            break;

        default:
            cout << "[-] Unsupported operation - exiting!" << endl;
            break;
        }

        next(&op);
    } while (op.id != UNKNOWN && op.id != EXIT);

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
