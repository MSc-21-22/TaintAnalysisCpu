#pragma once
#include <future>

void init_gpu();
std::future<void> init_gpu_async();