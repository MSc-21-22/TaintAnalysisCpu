#pragma once

void malloc_pinned(void** ptr, unsigned int byte_count);

void free_pinned(void* ptr);