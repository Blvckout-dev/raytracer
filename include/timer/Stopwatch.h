#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
private:
    std::chrono::high_resolution_clock::time_point _start = std::chrono::high_resolution_clock::now();
public:
    void restart() {
        _start = std::chrono::high_resolution_clock::now();
    }

    double elapsedMs() const {
        return std::chrono::duration<double, std::milli>(
            std::chrono::high_resolution_clock::now() - _start
        ).count();
    }
};

#endif // STOPWATCH_H
