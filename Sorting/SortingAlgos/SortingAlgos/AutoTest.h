#pragma once
#include <string>

class AutoTest {
public:
    AutoTest();
    ~AutoTest();

    void RunTest(int algorithm, int size, const std::string& outputFile);
    void RunBatch(int algorithm, int minSize, int maxSize, int stepSize, const std::string& outputFile);

private:
    int* generateArray(int size);
    void saveResults(const std::string& filename, int size, double timeMs, int algorithm);
};

