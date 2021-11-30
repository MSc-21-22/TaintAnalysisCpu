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
ReturnType time_func(std::string message, F func, Args&&... args){
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
void time_func(std::string message, F func, Args&&... args){
    if(timing::should_benchmark){
        TimeVar start = std::chrono::high_resolution_clock::now();

        func(std::forward<Args>(args)...);

        TimeVar end = std::chrono::high_resolution_clock::now();
        std::cout << message << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " μs" << std::endl;
    }else{
        func(std::forward<Args>(args)...);
    }

}

class Microseconds{
public:
    using chrono_type = std::chrono::microseconds;
    static constexpr const char* unit(){
        return "μs";
    }
};

class Stopwatch{
public:
    Stopwatch();
    void start();
    void stop();

    template<typename TimeUnit>
    void print_time(std::string message){
        if(timing::should_benchmark){
            std::cout << message << get_time<TimeUnit>() << " " << TimeUnit::unit() << std::endl;
        }
    }

    template<typename TimeUnit>
    void save_time(){
        std::fstream fout;
        fout.open("timings.csv", std::ios::out | std::ios::app);

        fout << get_time<TimeUnit>() << ",";   
    }

    static void add_line(){
        std::fstream fout;
        fout.open("timings.csv", std::ios::out | std::ios::app);

        fout << "\n";   
    }

private:
    TimeVar startTime;
    std::chrono::duration<double> duration;
    bool running;

    template<class TimeUnit, typename UnitType = typename TimeUnit::chrono_type>
    int64_t get_time(){
        if(running){
            stop();
        }
        return std::chrono::duration_cast<UnitType>(duration).count();
    }
};


