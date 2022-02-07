#pragma once

template<typename T>
T* malloc_pinned(size_t byte_count);

void free_pinned(void* ptr);