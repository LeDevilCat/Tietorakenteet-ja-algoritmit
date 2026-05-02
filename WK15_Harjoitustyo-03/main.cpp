#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Key.h"
#include "Search.h"
#include "Sort.h"
#include "TIMER.h"

using namespace std;

// Generate data: 1, 3, 5, ..., 2n-1 for n elements
void generateOddSequence(Key* data, int size) {
    for (int i = 0; i < size; i++) {
        data[i] = Key(2 * i + 1);
    }
}

// Generate random data in range 0 to 10*size
void generateRandomData(Key* data, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        data[i] = Key(rand() % (10 * size + 1));
    }
}

// Display first n elements
void displayData(Key* data, int size, int displayCount) {
    if (displayCount > size) displayCount = size;
    cout << "First " << displayCount << " elements: ";
    for (int i = 0; i < displayCount; i++) {
        cout << data[i].getValue();
        if (i < displayCount - 1) cout << ", ";
    }
    cout << endl;
}

// ==================== CHOICE 1: Linear Searching ====================
void linearSearching() {
    cout << "\n=== Linear Search ===" << endl;
    
    int size;
    cout << "Enter the size of dataset: ";
    cin >> size;
    
    Key* data = new Key[size];
    generateOddSequence(data, size);
    
    cout << "Generated data: ";
    for (int i = 0; i < size; i++) {
        cout << data[i].getValue();
        if (i < size - 1) cout << ", ";
    }
    cout << endl;
    
    int target;
    cout << "Enter value to search: ";
    cin >> target;
    
    Key searchKey(target);
    int result = Search::linearSearch(data, size, searchKey);
    
    if (result != -1) {
        cout << "Found at position: " << result << endl;
    } else {
        cout << "Value not found!" << endl;
    }
    
    delete[] data;
}

// ==================== CHOICE 2: Binary Searching ====================
void binarySearching() {
    cout << "\n=== Binary Search ===" << endl;
    
    int size;
    cout << "Enter the size of dataset: ";
    cin >> size;
    
    Key* data = new Key[size];
    generateOddSequence(data, size);
    
    cout << "Generated sorted data: ";
    for (int i = 0; i < size; i++) {
        cout << data[i].getValue();
        if (i < size - 1) cout << ", ";
    }
    cout << endl;
    
    int target;
    cout << "Enter value to search: ";
    cin >> target;
    
    Key searchKey(target);
    int result = Search::binarySearch(data, size, searchKey);
    
    if (result != -1) {
        cout << "Found at position: " << result << endl;
    } else {
        cout << "Value not found!" << endl;
    }
    
    delete[] data;
}

// ==================== CHOICE 3: n^2 Sorting ====================
void quadraticSorting() {
    cout << "\n=== O(n^2) Sorting (Insertion Sort) ===" << endl;
    
    int size;
    cout << "Enter the size of dataset: ";
    cin >> size;
    
    Key* data = new Key[size];
    generateRandomData(data, size);
    
    int displayCount;
    cout << "How many elements to display before/after sorting: ";
    cin >> displayCount;
    
    cout << "\nBefore sorting:" << endl;
    displayData(data, size, displayCount);
    
    Key::resetCounters();
    Sort::insertionSort(data, size);
    
    cout << "\nAfter sorting:" << endl;
    displayData(data, size, displayCount);
    
    cout << "Comparisons: " << Key::getComparisons() << endl;
    cout << "Assignments: " << Key::getAssignments() << endl;
    cout << "Total operations: " << (Key::getComparisons() + Key::getAssignments()) << endl;
    
    delete[] data;
}

// ==================== CHOICE 4: n*log(n) Sorting ====================
void nLogNSorting() {
    cout << "\n=== O(n log n) Sorting (Merge Sort) ===" << endl;
    
    int size;
    cout << "Enter the size of dataset: ";
    cin >> size;
    
    Key* data = new Key[size];
    generateRandomData(data, size);
    
    int displayCount;
    cout << "How many elements to display before/after sorting: ";
    cin >> displayCount;
    
    cout << "\nBefore sorting:" << endl;
    displayData(data, size, displayCount);
    
    Key::resetCounters();
    Sort::mergeSort(data, size);
    
    cout << "\nAfter sorting:" << endl;
    displayData(data, size, displayCount);
    
    cout << "Comparisons: " << Key::getComparisons() << endl;
    cout << "Assignments: " << Key::getAssignments() << endl;
    cout << "Total operations: " << (Key::getComparisons() + Key::getAssignments()) << endl;
    
    delete[] data;
}

// ==================== CHOICE 5: Performance Inspection ====================
void performanceInspection() {
    cout << "\n=== Performance Inspection ===" << endl;
    cout << "Comparing: Insertion Sort, Selection Sort, Merge Sort, Quick Sort" << endl;
    
    int maxSize;
    cout << "Enter maximum dataset size: ";
    cin >> maxSize;
    
    int step;
    cout << "Enter step size (e.g., 100 for 100, 200, 300...): ";
    cin >> step;
    
    // CSV output files
    ofstream csvComparisons("performance_comparisons.csv");
    ofstream csvAssignments("performance_assignments.csv");
    ofstream csvTime("performance_time.csv");
    
    // Write headers
    csvComparisons << "Size,InsertionSort,SelectionSort,MergeSort,QuickSort" << endl;
    csvAssignments << "Size,InsertionSort,SelectionSort,MergeSort,QuickSort" << endl;
    csvTime << "Size,InsertionSort,SelectionSort,MergeSort,QuickSort" << endl;
    
    cout << "\nTesting algorithms..." << endl;
    cout << "Size\tInsertion\tSelection\tMerge\t\tQuick" << endl;
    cout << "====\t=========\t=========\t=====\t\t=====" << endl;
    
    for (int currentSize = step; currentSize <= maxSize; currentSize += step) {
        cout << currentSize << "\t";
        cout.flush();
        
        csvComparisons << currentSize << ",";
        csvAssignments << currentSize << ",";
        csvTime << currentSize << ",";
        
        // Insertion Sort
        Key* data1 = new Key[currentSize];
        generateRandomData(data1, currentSize);
        Key::resetCounters();
        Timer timer;
        Sort::insertionSort(data1, currentSize);
        double insertionTime = timer.elapsed_time();
        cout << Key::getComparisons() << "+\t";
        cout.flush();
        csvComparisons << Key::getComparisons() << ",";
        csvAssignments << Key::getAssignments() << ",";
        csvTime << insertionTime << ",";
        delete[] data1;
        
        // Selection Sort
        Key* data2 = new Key[currentSize];
        generateRandomData(data2, currentSize);
        Key::resetCounters();
        timer.reset();
        Sort::selectionSort(data2, currentSize);
        double selectionTime = timer.elapsed_time();
        cout << Key::getComparisons() << "+\t";
        cout.flush();
        csvComparisons << Key::getComparisons() << ",";
        csvAssignments << Key::getAssignments() << ",";
        csvTime << selectionTime << ",";
        delete[] data2;
        
        // Merge Sort
        Key* data3 = new Key[currentSize];
        generateRandomData(data3, currentSize);
        Key::resetCounters();
        timer.reset();
        Sort::mergeSort(data3, currentSize);
        double mergeTime = timer.elapsed_time();
        cout << Key::getComparisons() << "+\t";
        cout.flush();
        csvComparisons << Key::getComparisons() << ",";
        csvAssignments << Key::getAssignments() << ",";
        csvTime << mergeTime << ",";
        delete[] data3;
        
        // Quick Sort
        Key* data4 = new Key[currentSize];
        generateRandomData(data4, currentSize);
        Key::resetCounters();
        timer.reset();
        Sort::quickSort(data4, currentSize);
        double quickTime = timer.elapsed_time();
        cout << Key::getComparisons() << endl;
        csvComparisons << Key::getComparisons() << endl;
        csvAssignments << Key::getAssignments() << endl;
        csvTime << quickTime << endl;
        delete[] data4;
    }
    
    csvComparisons.close();
    csvAssignments.close();
    csvTime.close();
    
    cout << "\nPerformance data saved to:" << endl;
    cout << "  - performance_comparisons.csv" << endl;
    cout << "  - performance_assignments.csv" << endl;
    cout << "  - performance_time.csv" << endl;
    cout << "\nYou can use these files to create graphs (e.g., with Excel, Python, etc.)" << endl;
}

// ==================== Main Menu ====================
int main() {
    cout << "Search and Sort Testing Application" << endl;
    cout << "====================================" << endl;
    
    int choice;
    bool running = true;
    
    while (running) {
        cout << "\n1) Linear searching" << endl;
        cout << "2) Binary searching" << endl;
        cout << "3) n^2 type sorting" << endl;
        cout << "4) n * log(n) type of sorting" << endl;
        cout << "5) Sorting algorithms performance inspection" << endl;
        cout << "6) Quit" << endl;
        cout << "Your choice: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                linearSearching();
                break;
            case 2:
                binarySearching();
                break;
            case 3:
                quadraticSorting();
                break;
            case 4:
                nLogNSorting();
                break;
            case 5:
                performanceInspection();
                break;
            case 6:
                cout << "Exiting program." << endl;
                running = false;
                break;
            default:
                cout << "Choice " << choice << " not implemented" << endl;
        }
    }
    
    return 0;
}
