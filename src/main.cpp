#include <iostream>
#include <fstream>
#include <list>

#include "runner.hpp"
#include "mergeable_heap.hpp"

using namespace std;

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

int main(int argc, char **argv)
{
    list<MergeableHeap> heaps;
    list<MergeableHeap>::iterator it;
    Runner runner;

    if (argc > 2) {
        std::cout << "[!] Usage: ./main.exe optional_path\n";
        return 1;
    }

    if (argc == 2) {
        runner = Runner(argv[1]);
    } else {
        runner = Runner();
    }

    runner.run(&heaps);

    for (it = heaps.begin(); it != heaps.end(); it++) {
        it->print();
    }

    return 0;
}
