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

class AutoTestFloat {
public:
    AutoTestFloat();
    void RunBatchFloat(int poolSize, int arraySize, const std::string& summaryFile);
private:
    float* generateArrayFloat(int size);
    double runSingleTestFloat(float* data, int size);
    void saveResultsFloat(const std::string& summaryFile, const std::string& detailFile,
        int size, double avgTimeMs, double medianMs, double stdDevMs,
        int poolSize, double* times);
};
class AutoTestLong {
public:
    AutoTestLong();
    void RunBatchLong(int poolSize, int arraySize, const std::string& summaryFile);
private:
    long long int* generateArrayLong(int size);
    double runSingleTestLong(long long int* data, int size);
    void saveResultsLong(const std::string& summaryFile, const std::string& detailFile,
        int size, double avgTimeMs, double medianMs, double stdDevMs,
        int poolSize, double* times);
};