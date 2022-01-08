#include <iostream>
#include <fstream>
#include <list>
#include <string.h>

#include "runner.hpp"
#include "mergeable_heap.hpp"

using namespace std;

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

int main(int argc, char **argv)
{
    list<MergeableHeap> heaps;
    list<MergeableHeap>::iterator it;
    Runner runner;
    Mode mode;

    if (argc == 2) {
        runner = Runner(argv[1]);
    } else if (argc == 1) {
        runner = Runner();
    } else {
        cout << "[!] Usage: ./maman14.exe [path(optional)]\n";
        return 1;
    }

    mode = runner.select_mode();
    if (mode == UNSUPPORTED) {
        cout << "[-] Unsupported mergeable heap type! Use sorted/unsorted/foreign" << endl;
        return 1;
    }

    runner.run(&heaps, mode);

    for (it = heaps.begin(); it != heaps.end(); it++) {
        it->print();
    }

    return 0;
}
