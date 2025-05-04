#pragma once
class Sorter {
public:
    Sorter(int* data, int size);
    void runSort(int algorithm);
    void insertionSort();
    void binaryInsertionSort();
    void heapSort(); // Now implemented from scratch
    void quickSort();
    void printArray();
    void drunkInsertion();

private:
     int* arr;
     int size;
    // Helpers
    void quickSortHelper(int low, int high);
    int partition(int low, int high);

    // Heap helpers
    void heapify(int n, int i);
    void swap(int& a, int& b);
};
