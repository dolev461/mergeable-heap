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

    if (argc == 3) {
        runner = Runner(argv[2]);
    } else if (argc == 2) {
        runner = Runner();
    } else {
        cout << "[!] Usage: ./maman14.exe [sorted, unsorted, foreign] [path]\n";
        return 1;
    }

    if (strcmp(argv[1], "sorted") == 0) {
        mode = SORTED;
    }
    else if (strcmp(argv[1], "unsorted") == 0) {
        mode = UNSORTED;
    }
    else if (strcmp(argv[1], "foreign") == 0) {
        mode = FOREIGN;
    }
    else {
        cout << "[-] Unsupported mergeable heap type! Use sorted/unsorted/foreign" << endl;
        return 1;
    }

    runner.run(&heaps, mode);

    for (it = heaps.begin(); it != heaps.end(); it++) {
        it->print();
    }

    return 0;
}
