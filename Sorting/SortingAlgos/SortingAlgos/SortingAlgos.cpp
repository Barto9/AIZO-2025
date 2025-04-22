#include <iostream>
#include <thread>
#include "Timer.h"
#include "Fileloader.h"
#include "Sorter.h"

int main() {
    Timer timer;
    Fileloader fileloader;
    fileloader.LoadFile("test.txt");
    std::cout << "File loaded successfully." << std::endl;
    fileloader.DisplayArray();
    Sorter sorter(fileloader.array, fileloader.size);
    sorter.quickSort();
    sorter.printArray();
    return 0;
}
