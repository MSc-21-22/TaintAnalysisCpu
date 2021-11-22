#include "timing.h"

namespace timing{
    bool should_benchmark = false;
}

Stopwatch::Stopwatch(){
    start();
}

void Stopwatch::start(){
    running = true;
    startTime = std::chrono::high_resolution_clock::now();
}

void Stopwatch::stop(){
    running = false;
    auto endTime = std::chrono::high_resolution_clock::now();
    duration += endTime - startTime;
}

int64_t Stopwatch::get_time_microseconds(){
    if(running){
        stop();
    }
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

void Stopwatch::saveTimeMicroseconds(){
    std::fstream fout;
    fout.open("timings.csv", std::ios::out | std::ios::app);

    fout << get_time_microseconds() << ",";   
}

void Stopwatch::printTimeMicroseconds(std::string message){
    if(timing::should_benchmark){
        std::cout << message << get_time_microseconds() << " μs" << std::endl;
    }
}