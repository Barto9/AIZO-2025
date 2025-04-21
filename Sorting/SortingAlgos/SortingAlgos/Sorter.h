#pragma once
#ifndef SORTER_H
#define SORTER_H

#include <vector>

class Sorter {
public:
    Sorter(std::vector<int> data);
    void insertionSort();
    void binaryInsertionSort();
    void heapSort(); // Now implemented from scratch
    void quickSort();
    std::vector<int> getArray();

private:
    std::vector<int> arr;

    // Helpers
    void quickSortHelper(int low, int high);
    int partition(int low, int high);

    // Heap helpers
    void heapify(int n, int i);
    void swap(int& a, int& b);
};

#endif // SORTER_H
