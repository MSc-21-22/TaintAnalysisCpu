#pragma once

void cuda_allocate_memory(void **devPtr, size_t size);
void cuda_copy_to_device(void *dst, const void *src, size_t size);
void cuda_copy_to_host(void *dst, const void *src, size_t size);