#include <iostream>
#include <thread>
#include "Timer.h"
#include "Fileloader.h"
#include "Sorter.h"
#include "AutoTest.h"

void showHelp() {
    std::cout << "FILE TEST MODE:\n"
        << "Usage:\n"
        << "./SortingAlgos --file <algorithm> <type> <inputFile> <outputFile>\n"
        << "<algorithm> Sorting algorithm to use (e.g., 1 - InsertionBinary, 2 - Insertion, 3 - Heapsort, 4 - Quicksort).\n"
        << "<type> Data type to load (0 - int only for now).\n"
        << "<inputFile> Input file containing the data to be sorted.\n"
        << "[outputFile] If provided, the sorted values will be saved to this file.\n\n"
        << "BENCHMARK MODE:\n"
        << "Usage:\n"
        << "./SortingAlgos --test <algorithm> <type> <arraysize> <outputFile>\n"
        << "<algorithm> Sorting algorithm to use.\n"
        << "<type> Data type to generate (0 - int only for now).\n"
        << "<size> Number of elements to generate.\n"
        << "<outputFile> File where the benchmark results will be saved.\n\n"
        << "BATCH BENCHMARK:\n"
        << "./SortingAlgos --batchtest <algorithm> <type> <poolSize> <size> <outputFile>\n"
        << "Runs tests for multiple sizes.\n\n"
        << "HELP MODE:\n"
        << "Usage:\n"
        << "./SortingAlgos --help\n"
        << "Displays this help message.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2 || std::string(argv[1]) == "--help") {
        showHelp();
        return 0;
    }

    std::string mode = argv[1];

    if (mode == "--file" && argc >= 5) {
        int algorithm = std::stoi(argv[2]);
        int type = std::stoi(argv[3]); // Currently only 0 (int) supported
        std::string inputFile = argv[4];
        std::string outputFile = (argc >= 6) ? argv[5] : "";

        if (type != 0) {
            std::cerr << "Only int (type 0) is supported for now.\n";
            return 1;
        }

        Fileloader loader;
        if (loader.LoadFile(inputFile) != 0) return 1;

        Timer timer;
        Sorter sorter(loader.array, loader.size);
        timer.start();
        sorter.runSort( algorithm);
        timer.stop();

        std::cout << "Sorted array:\n";
        sorter.printArray();
        std::cout << "Time elapsed: " << timer.result() << " ms\n";

        if (!outputFile.empty()) {
            loader.SaveToFile(outputFile);
        }

    }
    else if (mode == "--test" && argc == 6) {
        int algorithm = std::stoi(argv[2]);
        int type = std::stoi(argv[3]);
        int size = std::stoi(argv[4]);
        std::string outputFile = argv[5];

        if (type != 0) {
            std::cerr << "Only int (type 0) is supported for now.\n";
            return 1;
        }

        int* data = new int[size];
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 0; i < size; ++i)
            data[i] = rand();

        Sorter sorter(data, size);
        Timer timer;
        timer.start();
        sorter.runSort(algorithm);
        timer.stop();

        std::ofstream out(outputFile);
        if (!out) {
            std::cerr << "Failed to open output file.\n";
            delete[] data;
            return 1;
        }

        out << "Sorted " << size << " elements in " << timer.result() << " ms\n";
        for (int i = 0; i < size; ++i)
            out << data[i] << " ";
        out << std::endl;

        delete[] data;
        std::cout << "Benchmark complete. Results saved to " << outputFile << "\n";

    }
    else if (mode == "--batchtest" && argc == 7) {
        int algorithm = std::stoi(argv[2]);
        int type = std::stoi(argv[3]);
        int poolSize = std::stoi(argv[4]);
        int arraySize = std::stoi(argv[5]);
        std::string outFile = argv[6];

        if (type != 0) {
            std::cerr << "Only int type (0) is supported in batch test mode.\n";
            return 1;
        }

        AutoTest test;
        test.RunBatch(algorithm, poolSize, arraySize, outFile);
    }
    else if (mode == "--drunk" && argc == 7) {
        int algorithm = std::stoi(argv[2]);
        int poolSize = std::stoi(argv[3]);
        int arraySize = std::stoi(argv[4]);
        int drunkness = std::stoi(argv[5]);
        std::string outFile = argv[6];

        AutoTest test;
        test.RunBatch(algorithm, poolSize, arraySize, outFile);
    }
    else {
        showHelp();
        return 1;
    }

    return 0;
}

/*int main() {
    Timer timer;
    Fileloader fileloader;
    fileloader.LoadFile("test.txt");
    std::cout << "File loaded successfully." << std::endl;
    fileloader.DisplayArray();
    Sorter sorter(fileloader.array, fileloader.size);
    sorter.quickSort();
    sorter.printArray();
    return 0;
}*/
