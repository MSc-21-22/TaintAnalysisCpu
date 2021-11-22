#pragma once

#include <chrono>
#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>
#include <ios>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

namespace timing{
    extern bool should_benchmark;
}

template<typename ReturnType, typename F, typename... Args>
ReturnType timeFunc(std::string message, F func, Args&&... args){
    if(timing::should_benchmark){
        TimeVar start = std::chrono::high_resolution_clock::now();

        ReturnType result = func(std::forward<Args>(args)...);

        TimeVar end = std::chrono::high_resolution_clock::now();
        std::cout << message << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " μs" << std::endl;
        return result;
    }else{
        return func(std::forward<Args>(args)...);
    }
}

template<typename F, typename... Args>
void timeFunc(std::string message, F func, Args&&... args){
    if(timing::should_benchmark){
        TimeVar start = std::chrono::high_resolution_clock::now();

        func(std::forward<Args>(args)...);

        TimeVar end = std::chrono::high_resolution_clock::now();
        std::cout << message << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " μs" << std::endl;
    }else{
        func(std::forward<Args>(args)...);
    }

}

class Stopwatch{
public:
    Stopwatch();
    void start();
    void stop();
    void printTimeMicroseconds(std::string message);
    void saveTimeMicroseconds();
    static void add_line(){
        std::fstream fout;
        fout.open("timings.csv", std::ios::out | std::ios::app);

        fout << "\n";   
    }

private:
    TimeVar startTime;
    std::chrono::duration<double> duration;
    bool running;

    int64_t get_time_microseconds();
};


