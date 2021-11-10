#pragma once

#include <chrono>
#include <utility>
#include <functional>
#include <iostream>
#include <string>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

template<typename ReturnType, typename F, typename... Args>
ReturnType timeFunc(std::string message, F func, Args&&... args){
    TimeVar start = std::chrono::high_resolution_clock::now();

    ReturnType result = func(std::forward<Args>(args)...);

    TimeVar end = std::chrono::high_resolution_clock::now();
    std::cout << message << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " μs" << std::endl;
    return result;
}

template<typename F, typename... Args>
void timeFunc(std::string message, F func, Args&&... args){
    TimeVar start = std::chrono::high_resolution_clock::now();

    func(std::forward<Args>(args)...);

    TimeVar end = std::chrono::high_resolution_clock::now();
    std::cout << message << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " μs" << std::endl;
}

class Stopwatch{
public:
    Stopwatch();
    void start();
    void stop();
    void printTimeMicroseconds(std::string message);

private:
    TimeVar startTime;
    std::chrono::duration<double> duration;
    bool running;
};


