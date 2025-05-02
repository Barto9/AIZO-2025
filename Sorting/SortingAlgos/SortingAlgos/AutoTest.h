#pragma once
#include <string>

class AutoTest {
public:
    AutoTest();
    void RunBatch(int algorithm, int poolSize, int arraySize, const std::string& summaryFile);

private:
    int* generateArray(int size);
    double runSingleTest(int algorithm, int* data, int size);
    void saveResults(const std::string& summaryFile, const std::string& detailFile,
        int size, double avgTimeMs, int algorithm, int poolSize, double* times);
};
