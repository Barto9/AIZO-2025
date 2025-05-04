#pragma once
#include <string>

class AutoTest {
public:
    AutoTest();
    void RunBatch(int algorithm, int poolSize, int arraySize, int distrType, const std::string& summaryFile);
    void RunBatchDrunk(int poolSize, int arraySize, int drunkness, int distrType, const std::string& summaryFile);
private:
    int* generateArray(int size, int distrType);
    double runSingleTest(int algorithm, int* data, int size);
    double runSingleTestDrunk(int drunkness, int* data, int size);
    void saveResults(const std::string& summaryFile, const std::string& detailFile,
        int size, double avgTimeMs, double medianMs, double stdDevMs,
        int algorithm, int poolSize, double* times);
};
