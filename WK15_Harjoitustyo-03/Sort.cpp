#include "Sort.h"

// ==================== O(n^2) Algorithms ====================

void Sort::insertionSort(Key* data, int size) {
    for (int i = 1; i < size; i++) {
        Key key = data[i];
        int j = i - 1;
        
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

void Sort::selectionSort(Key* data, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < size; j++) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap
        Key temp = data[i];
        data[i] = data[minIndex];
        data[minIndex] = temp;
    }
}

// ==================== O(n log n) Algorithms ====================

void Sort::mergeSort(Key* data, int size) {
    if (size <= 1) return;
    
    Key* temp = new Key[size];
    
    // Start with merge subarrays of size 1, then 2, then 4, etc.
    for (int currSize = 1; currSize < size; currSize = 2 * currSize) {
        for (int leftStart = 0; leftStart < size; leftStart += 2 * currSize) {
            int mid = leftStart + currSize;
            int rightEnd = leftStart + 2 * currSize;
            if (rightEnd > size) rightEnd = size;
            if (mid > size) mid = size;
            
            if (mid < rightEnd) {
                merge(data, leftStart, mid, rightEnd);
            }
        }
    }
    
    delete[] temp;
}

void Sort::merge(Key* data, int left, int mid, int right) {
    Key* temp = new Key[right - left];
    int i = left, j = mid, k = 0;
    
    while (i < mid && j < right) {
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }
    
    while (i < mid) {
        temp[k++] = data[i++];
    }
    while (j < right) {
        temp[k++] = data[j++];
    }
    
    for (int i = left, k = 0; i < right; i++, k++) {
        data[i] = temp[k];
    }
    
    delete[] temp;
}

void Sort::quickSort(Key* data, int size) {
    if (size > 1) {
        quickSortHelper(data, 0, size - 1);
    }
}

void Sort::quickSortHelper(Key* data, int left, int right) {
    if (left < right) {
        int pi = partition(data, left, right);
        quickSortHelper(data, left, pi - 1);
        quickSortHelper(data, pi + 1, right);
    }
}

int Sort::partition(Key* data, int left, int right) {
    Key pivot = data[right];
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        if (data[j] < pivot) {
            i++;
            Key temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    
    Key temp = data[i + 1];
    data[i + 1] = data[right];
    data[right] = temp;
    
    return i + 1;
}
