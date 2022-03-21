#include "timing.h"

namespace timing{
    bool should_benchmark = false;
}

Stopwatch::Stopwatch(){
    startTime = std::chrono::high_resolution_clock::now();
}