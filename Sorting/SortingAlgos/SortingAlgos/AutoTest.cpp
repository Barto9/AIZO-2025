#include "AutoTest.h"
#include "Sorter.h"
#include "Timer.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

AutoTest::AutoTest() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

AutoTest::~AutoTest() {
    // Nothing to clean
}

int* AutoTest::generateArray(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 100000;
    return arr;
}

void AutoTest::saveResults(const std::string& filename, int size, double timeMs, int algorithm) {
    std::ofstream out(filename, std::ios::app); // append mode
    if (!out) {
        std::cerr << "Error: Cannot open result file.\n";
        return;
    }
    out << algorithm << "," << size << "," << timeMs << "\n";
}

void AutoTest::RunTest(int algorithm, int size, const std::string& outputFile) {
    int* data = generateArray(size);
    Sorter sorter(data, size);

    Timer timer;
    switch (algorithm) {
    case 1: sorter.binaryInsertionSort; break;
    case 2: sorter.insertionSort(); break;
    case 3: sorter.quickSort(); break;
    case 4: sorter.heapSort(); break;
    default:
        std::cerr << "Unsupported algorithm.\n";
        delete[] data;
        return;
    }
    timer.stop();

    double elapsed = timer.result();
    std::cout << "Sorted " << size << " items using algorithm " << algorithm
        << " in " << elapsed << " ms\n";

    saveResults(outputFile, size, elapsed, algorithm);
    delete[] data;
}

void AutoTest::RunBatch(int algorithm, int minSize, int maxSize, int stepSize, const std::string& outputFile) {
    for (int size = minSize; size <= maxSize; size += stepSize) {
        RunTest(algorithm, size, outputFile);
    }
}
