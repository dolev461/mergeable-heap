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

        Mode select_mode();
        bool run(list<MergeableHeap> * heaps, Mode mode);

    private:
        void next(Operation * op);

        ifstream _file;
};