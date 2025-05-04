#include "AutoTest.h"
#include "Sorter.h"
#include "Timer.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

AutoTest::AutoTest() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

int* AutoTest::generateArray(int size, int distrType) {
    int* arr = new int[size];
    for (int i = 0; i < size; ++i)
        arr[i] = rand();
    //IMPORTANT I USE std : sort her to minimize running time(it's most likely better that any of my algorythms)

    return arr;
}

double AutoTest::runSingleTest(int algorithm, int* data, int size) {
    int* arrCopy = new int[size];
    for (int i = 0; i < size; ++i)
        arrCopy[i] = data[i];

    Sorter sorter(arrCopy, size);
    Timer timer;
    timer.start();
    sorter.runSort(algorithm);
    timer.stop();
    double elapsed = timer.result();
    delete[] arrCopy;
    return elapsed;
}

void AutoTest::saveResults(const std::string& summaryFile, const std::string& detailFile,
    int size, double avgTimeMs, double medianMs, double stdDevMs, int algorithm, int poolSize, double* times) {

    // Save summary
    std::ofstream out(summaryFile, std::ios::app);
    if (!out) {
        std::cerr << "Error: Cannot open summary file.\n";
        return;
    }

    // If it's the first write, add header
    static bool headerWritten = false;
    if (!headerWritten) {
        out << "Algorithm;Size;PoolSize;AvgTimeMs;MedianMs;StdDevMs\n";
        headerWritten = true;
    }

    out << algorithm << ";" << size << ";" << poolSize << ";"
        << avgTimeMs << ";" << medianMs << ";" << stdDevMs << "\n";
    out.close();

    // Save detailed run times
    std::ofstream detail(detailFile);
    if (!detail) {
        std::cerr << "Error: Cannot open detail file.\n";
        return;
    }

    detail << "Run;Time(ms)\n";
    for (int i = 0; i < poolSize; ++i)
        detail << (i + 1) << ";" << times[i] << "\n";

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

    // Compute average
    double avgTime = totalTime / poolSize;

    // Compute median IMPORTANT I USE std:sort her to minimize running time (it's most likely better that any of my algorythms)
    std::sort(times, times + poolSize);
    double median = (poolSize % 2 == 0)
        ? (times[poolSize / 2 - 1] + times[poolSize / 2]) / 2.0
        : times[poolSize / 2];

    // Compute standard deviation
    double variance = 0.0;
    for (int i = 0; i < poolSize; ++i)
        variance += (times[i] - avgTime) * (times[i] - avgTime);
    double stdDev = std::sqrt(variance / poolSize);

    // Construct detail filename with parameters
    std::string detailFile = "detailed_alg" + std::to_string(algorithm)
        + "_pool" + std::to_string(poolSize)
        + "_size" + std::to_string(arraySize) + ".csv";

    std::cout << "Algorithm " << algorithm << " | Size " << arraySize
        << " | Pool " << poolSize << " | Avg: " << avgTime
        << " ms | Median: " << median << " ms | StdDev: " << stdDev << "\n";

    saveResults(summaryFile, detailFile, arraySize, avgTime, median, stdDev, algorithm, poolSize, times);
    delete[] times;
}

void AutoTest::RunBatchDrunk(int poolSize, int arraySize, int drunkness, const std::string& summaryFile) {
    double* times = new double[poolSize];
    double totalTime = 0.0;
    int algorithm = 5;
    for (int i = 0; i < poolSize; ++i) {
        int* data = generateArray(arraySize);
        double elapsed = runSingleTest(algorithm, data, arraySize);
        times[i] = elapsed;
        totalTime += elapsed;
        delete[] data;
    }

    // Compute average
    double avgTime = totalTime / poolSize;

    // Compute median IMPORTANT I USE std:sort her to minimize running time (it's most likely better that any of my algorythms)
    std::sort(times, times + poolSize);
    double median = (poolSize % 2 == 0)
        ? (times[poolSize / 2 - 1] + times[poolSize / 2]) / 2.0
        : times[poolSize / 2];

    // Compute standard deviation
    double variance = 0.0;
    for (int i = 0; i < poolSize; ++i)
        variance += (times[i] - avgTime) * (times[i] - avgTime);
    double stdDev = std::sqrt(variance / poolSize);

    // Construct detail filename with parameters
    std::string detailFile = "detailed_alg" + std::to_string(algorithm)
        + "_pool" + std::to_string(poolSize)
        + "_size" + std::to_string(arraySize) + ".csv";

    std::cout << "Algorithm " << algorithm << " | Size " << arraySize
        << " | Pool " << poolSize << " | Avg: " << avgTime
        << " ms | Median: " << median << " ms | StdDev: " << stdDev << "\n";

    saveResults(summaryFile, detailFile, arraySize, avgTime, median, stdDev, algorithm, poolSize, times);
    delete[] times;
}
