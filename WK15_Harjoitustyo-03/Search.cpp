#include "Search.h"

// Linear search - sequential search from start to end
int Search::linearSearch(Key* data, int size, Key target) {
    for (int i = 0; i < size; i++) {
        if (data[i] == target) {
            return i + 1;  // Return 1-based index
        }
    }
    return -1;  // Not found
}

// Binary search - requires sorted data
int Search::binarySearch(Key* data, int size, Key target) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (data[mid] == target) {
            return mid + 1;  // Return 1-based index
        }
        else if (data[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;  // Not found
}
