#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
public:
    Timer();
    void reset();
    double elapsed();
};

#endif 
