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

int* AutoTest::generateArray(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 100000;
    return arr;
}

double AutoTest::runSingleTest(int algorithm, int* data, int size) {
    int* arrCopy = new int[size];
    for (int i = 0; i < size; ++i)
        arrCopy[i] = data[i];

    Sorter sorter(arrCopy, size);
    Timer timer;

    switch (algorithm) {
    case 2: sorter.insertionSort(); break;
    case 3: sorter.quickSort(); break;
    case 4: sorter.heapSort(); break;
    default:
        std::cerr << "Unsupported algorithm.\n";
        delete[] arrCopy;
        return -1;
    }

    timer.stop();
    double elapsed = timer.result();
    delete[] arrCopy;
    return elapsed;
}

void AutoTest::saveResults(const std::string& summaryFile, const std::string& detailFile,
    int size, double avgTimeMs, int algorithm, int poolSize, double* times) {
    // Save summary
    std::ofstream out(summaryFile, std::ios::app);
    if (!out) {
        std::cerr << "Error: Cannot open summary file.\n";
        return;
    }
    out << algorithm << "," << size << "," << poolSize << "," << avgTimeMs << "\n";
    out.close();

    // Save detailed run times
    std::ofstream detail(detailFile);
    if (!detail) {
        std::cerr << "Error: Cannot open detail file.\n";
        return;
    }
    detail << "run_index,time_ms\n";
    for (int i = 0; i < poolSize; ++i)
        detail << (i + 1) << "," << times[i] << "\n";

    detail.close();
}

void AutoTest::RunBatch(int algorithm, int poolSize, int arraySize, const std::string& summaryFile) {
    double* times = new double[poolSize];
    double totalTime = 0.0;

    for (int i = 0; i < poolSize; ++i) {
        int* data = generateArray(arraySize);
        double elapsed = runSingleTest(algorithm, data, arraySize);
        times[i] = elapsed;
        totalTime += elapsed;
        delete[] data;
    }

    double avgTime = totalTime / poolSize;
    std::string detailFile = "detailed_" + summaryFile;

    std::cout << "Algorithm " << algorithm << " | Size " << arraySize
        << " | Pool " << poolSize << " | Avg: " << avgTime << " ms\n";

    saveResults(summaryFile, detailFile, arraySize, avgTime, algorithm, poolSize, times);
    delete[] times;
}
