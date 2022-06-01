#pragma once
#include <future>
#include <timing.h>

void init_gpu();
std::future<void> init_gpu_async();