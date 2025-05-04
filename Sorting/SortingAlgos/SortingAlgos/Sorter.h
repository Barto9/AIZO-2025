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
    void drunkInsertion(int drunkness);

private:

     int* arr;
     int size;
    // Helpers
    void quickSortHelper(int low, int high);
    bool isSorted(const int* arr, int size);
    int partition(int low, int high);

    // Heap helpers
    void heapify(int n, int i);
    void swap(int& a, int& b);
};

class SorterFloat {
public:
    SorterFloat(float* data, int size);
    void quickSort();
private:
    float* arr;
    int size;
    void quickSortHelper(int low, int high);
    int partition(int low, int high);
    void swap(float& a, float& b);
};

class SorterLong {
public:
    SorterLong(long long* data, int size);
    void quickSort();
private:
    long long* arr;
    int size;
    void quickSortHelper(int low, int high);
    int partition(int low, int high);
    void swap(long long& a, long long& b);
};