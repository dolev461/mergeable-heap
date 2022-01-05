#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

#include "operations.hpp"
#include "mergeable_heap.hpp"

using namespace std;

class Runner {
    public:
        Runner(); // Get operations from stdin
        Runner(string path); // Get operations from file

        void next(op_t * op);
        void print();

        bool run(list<MergeableHeap> * heaps);

    protected:
        ifstream _file;
};