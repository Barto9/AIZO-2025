#include <iostream>
#include <thread>
#include "Timer.h"

int main() {
    Timer timer;
    char command;

    while (true) {
        std::cout << "Press 's' to start, 'e' to stop, 'r' to reset, 'q' to quit: ";
        std::cin >> command;

        switch (command) {
        case 's':
            if (timer.start() == 0)
                std::cout << "Timer started.\n";
            else
                std::cout << "Timer is already running!\n";
            break;

        case 'e':
            if (timer.stop() == 0)
                std::cout << "Timer stopped. Elapsed time: " << timer.result() << " ms\n";
            else
                std::cout << "Timer is not running!\n";
            break;

        case 'r':
            timer.reset();
            std::cout << "Timer reset.\n";
            break;

        case 'q':
            std::cout << "Exiting...\n";
            return 0;

        default:
            std::cout << "Invalid input. Try again.\n";
            break;
        }
    }
}
