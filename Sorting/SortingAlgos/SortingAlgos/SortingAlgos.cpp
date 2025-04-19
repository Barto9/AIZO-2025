#include <iostream>
#include <thread>
#include "Timer.h"
#include "Fileloader.h"

int main() {
    Timer timer;
    Fileloader fileloader;
    fileloader.LoadFile("test.txt");
    std::cout << "File loaded successfully." << std::endl;
    fileloader.DisplayArray();
    return 0;
}
