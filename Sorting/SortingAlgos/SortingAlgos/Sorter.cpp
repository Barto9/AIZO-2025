#include "Sorter.h"
#include <iostream>

Sorter::Sorter(int* data, int size) {
    this->arr = data;
    this->size = size;
}
SorterFloat::SorterFloat(float* data, int size) : arr(data), size(size) {}
SorterLong::SorterLong(long long* data, int size) : arr(data), size(size) {}

void Sorter::runSort( int algorithm) {
    switch (algorithm) {
    case 1:
        binaryInsertionSort();
        break;
    case 2:
        insertionSort();
        break;
    case 3:
        quickSort();
        break;
    case 4:
        heapSort();
        break;
    default:
        std::cerr << "Algorithm not implemented.\n";
        exit(1);
    }
}

void Sorter::printArray() {
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
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

bool Sorter::isSorted(const int* arr, int size) 
{
    for (int i = 1; i < size; ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

void Sorter::drunkInsertion(int drunkness) {
    while (!isSorted(arr, size))
    {

        int error = 0;
        for (int i = 1; i < size; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            if (drunkness % 101 >= rand() % 101)
            {
                if (rand() % 2 && j+1 < size - 1)
                {
                    error = 1;
                }
                else if(j - 1 > 0)
                {
                    error = -1;
                }
                else 
                {
                    error = 0;
                }
            }
            arr[j + 1 + error] = key;
            error = 0;
        }
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

void Sorter::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
//float part bcs im stupid
void SorterFloat::quickSort() {
    quickSortHelper(0, size - 1);
}

void SorterFloat::quickSortHelper(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSortHelper(low, pi - 1);
        quickSortHelper(pi + 1, high);
    }
}

int SorterFloat::partition(int low, int high) {
    float pivot = arr[high];
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

void SorterFloat::swap(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}
//long long part bcs im stupider
void SorterLong::quickSort() {
    quickSortHelper(0, size - 1);
}

void SorterLong::quickSortHelper(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSortHelper(low, pi - 1);
        quickSortHelper(pi + 1, high);
    }
}

int SorterLong::partition(int low, int high) {
    long long pivot = arr[high];
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

void SorterLong::swap(long long& a, long long& b) {
    long long temp = a;
    a = b;
    b = temp;
}