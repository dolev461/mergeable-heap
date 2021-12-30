#include <iostream>
#include <fstream>

#include "operations_file.hpp"
#include "mergeable_heap.hpp"

using namespace std;

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "[!] Usage: ./main.exe OPERATION_FILE\n";
        return 1;
    }

    OperationsFile ops_file(argv[1]);
    ops_file.print();

    int l[] = {1, 2, 3};

    MergeableHeap heap(l, ARRAY_LENGTH(l));
    //cout << heap.get_min() << endl;

    return 0;
}
