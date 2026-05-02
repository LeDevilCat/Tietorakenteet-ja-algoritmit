#ifndef SORT_H
#define SORT_H

#include "Key.h"

class Sort {
public:
    // O(n^2) sorting algorithms
    static void insertionSort(Key* data, int size);
    static void selectionSort(Key* data, int size);
    
    // O(n log n) sorting algorithms
    static void mergeSort(Key* data, int size);
    static void quickSort(Key* data, int size);
    
private:
    // Helper functions
    static void merge(Key* data, int left, int mid, int right);
    static void quickSortHelper(Key* data, int left, int right);
    static int partition(Key* data, int left, int right);
};

#endif
