#include <iostream>
#include <fstream>
#include <list>
#include <string.h>

#include "runner.hpp"
#include "mergeable_heap.hpp"

using namespace std;

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

enum Result {
    SUCCESS = 0,
    FAILURE = 1,
};

int main(int argc, char **argv)
{
    /* Variable initializations */
    list<MergeableHeap*> mheaps;
    list<MergeableHeap*>::iterator it;
    Runner runner;
    Mode mode;

    if (argc == 2) {
        /* Use file input */
        runner = Runner(argv[1]);
    } else if (argc == 1) {
        /* Use user input */
        runner = Runner();
    } else {
        cout << "[!] Usage: ./maman14 [path(optional)]\n";
        return FAILURE;
    }

    mode = runner.select_mode();
    if (mode == UNSUPPORTED) {
        cout << "[-] Unsupported mergeable heap type! Use sorted/unsorted/foreign" << endl;
        return FAILURE;
    }

    runner.run(&mheaps, mode);

    cout << "\nFinal mergeable-heaps:" << endl;
    /* Memory cleanup */
    for (it = mheaps.begin(); it != mheaps.end(); it++) {
        (*it)->print();
        delete *it;
    }

    return SUCCESS;
}
