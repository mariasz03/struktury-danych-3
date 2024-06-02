#include "..\headers\Timer.hpp" // Klasa Timer mierzaca czas

Timer::Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

void Timer::reset() {
    start_time = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() {
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed_seconds = end_time - start_time;
    return elapsed_seconds.count();
}
