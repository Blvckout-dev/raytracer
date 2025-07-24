#ifndef TICKTIMER_H
#define TICKTIMER_H

#include <chrono>
#include <functional>
#include <thread>
#include <atomic>
#include <cmath>

class TickTimer {
private:
    std::thread _thread;
    std::atomic<bool> _running { false };
    
public:
    TickTimer() = default;
    ~TickTimer() { stop(); }

    std::function<void(double)> onTick;

    void start() {
        if (_running) return;
        _running = true;

        _thread = std::thread([=]() {
            using clock = std::chrono::steady_clock;
            auto lastTime = clock::now();

            while (_running) {
                auto now = clock::now();
                std::chrono::duration<double> delta = now - lastTime;
                double dt = delta.count();

                lastTime = now;

                if (onTick) {
                    onTick(dt);
                }
            }
        });
    }

    void stop() {
        _running = false;
        if (_thread.joinable())
            _thread.join();
    }

    bool isRunning() const { return _running; }
};

#endif // TIMER_H
