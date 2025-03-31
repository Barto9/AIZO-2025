#include "Timer.h"

Timer::Timer() : running(false) {}

void Timer::reset() {
    running = false;
}

int Timer::start() {
    if (!running) {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
        return 0;
    }
    return -1; // Timer already running
}

int Timer::stop() {
    if (running) {
        end_time = std::chrono::high_resolution_clock::now();
        running = false;
        return 0;
    }
    return -1; // Timer not running
}

int Timer::result() {
    if (!running) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }
    return -1; // Timer is still running
}
