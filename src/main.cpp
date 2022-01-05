#include <iostream>
#include <fstream>
#include <list>

#include "operations_file.hpp"
#include "mergeable_heap.hpp"

using namespace std;

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

int main(int argc, char **argv)
{
    list<MergeableHeap> heaps;
    list<MergeableHeap>::iterator it;

    if (argc < 2) {
        std::cout << "[!] Usage: ./main.exe OPERATION_FILE\n";
        return 1;
    }

    OperationsFile ops_file(argv[1]);
    ops_file.run(&heaps);

    for (it = heaps.begin(); it != heaps.end(); it++) {
        it->print();
    }

    return 0;
}
