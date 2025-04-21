#include "Sorter.h"

Sorter::Sorter(std::vector<int> data) : arr(std::move(data)) {}

std::vector<int> Sorter::getArray() {
    return arr;
}

void Sorter::insertionSort() {
    for (size_t i = 1; i < arr.size(); ++i) {
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
    for (size_t i = 1; i < arr.size(); ++i) {
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
    int n = arr.size();

    // Build max heap (heapify from bottom-up)
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]); // Move current root to end
        heapify(i, 0); // Heapify reduced heap
    }
}

void Sorter::heapify(int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(n, largest); // Recursively heapify the affected sub-tree
    }
}

void Sorter::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void Sorter::quickSort() {
    quickSortHelper(0, arr.size() - 1);
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
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}
