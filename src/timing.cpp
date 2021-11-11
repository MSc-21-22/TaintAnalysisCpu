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

void Stopwatch::printTimeMicroseconds(std::string message){
    if(running){
        stop();
    }
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    if(timing::should_benchmark){
        std::cout << message << time << " μs" << std::endl;
    }
}