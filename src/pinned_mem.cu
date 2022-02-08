#include <cublas.h>
#include <cuda.h>
void malloc_pinned(void** ptr, unsigned int byte_count){
    cudaMallocHost(ptr, byte_count);
}

void free_pinned(void* ptr){
    cudaFreeHost(ptr);
}