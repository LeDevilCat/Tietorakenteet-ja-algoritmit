#ifndef SEARCH_H
#define SEARCH_H

#include "Key.h"

class Search {
public:
    // Linear search - returns index (1-based) or -1 if not found
    static int linearSearch(Key* data, int size, Key target);
    
    // Binary search - requires sorted data
    // Returns index (1-based) or -1 if not found
    static int binarySearch(Key* data, int size, Key target);
};

#endif
