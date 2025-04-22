#include "Sorter.h"
#include <iostream>

Sorter::Sorter(int* data, int size) {
    this->arr = data;
    this->size = size;
}

void Sorter::printArray() {
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

void Sorter::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void Sorter::insertionSort() {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void Sorter::binaryInsertionSort() {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int left = 0;
        int right = i - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] > key)
                right = mid - 1;
            else
                left = mid + 1;
        }

        for (int j = i - 1; j >= left; --j)
            arr[j + 1] = arr[j];

        arr[left] = key;
    }
}

void Sorter::heapSort() {
    for (int i = size / 2 - 1; i >= 0; --i)
        heapify(size, i);

    for (int i = size - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(i, 0);
    }
}

void Sorter::heapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(n, largest);
    }
}

void Sorter::quickSort() {
    quickSortHelper(0, size - 1);
}

void Sorter::quickSortHelper(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSortHelper(low, pi - 1);
        quickSortHelper(pi + 1, high);
    }
}

int Sorter::partition(int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
