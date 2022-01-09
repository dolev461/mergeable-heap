#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

#include "operations.hpp"
#include "mergeable_heap.hpp"

using namespace std;

/* Handles operations from either file or stdin - supported operations can be found in operations.hpp*/
class Runner {
    public:
        /* Initialize a Runner instance with stdin as input */
        Runner();

        /* Initialize a Runner instance with file as input
        *
        * Arguments:
        *   path - Path to operations file
        */
        Runner(string path);

        /* Ask the user for required mergeable-heaps operations mode from stdin */
        Mode select_mode();

        /* Run operations input one by one
        *
        * Arguments:
        *   mheaps - Dynamic list of MergeableHeaps to create new mheaps
        *       *make sure to delete the created mheaps!
        *   mode - Operations mode of the mergeable-heaps
        */
        bool run(list<MergeableHeap*> * mheaps, Mode mode);

    private:
        /* Parse the next operation
        *
        * Arguments:
        *   op - Out parameter set with the values of the next operation to run
        */
        void next(Operation * op);

        /* Input file if exists */
        ifstream _file;
};