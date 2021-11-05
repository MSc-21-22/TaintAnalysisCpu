
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "kernel.h"
#include <iostream>

#include <stdio.h>

bool cudaMemcmp(const float *a, const float* b, int size);

__global__ void memcmp_kernel(const float* a, const float* b, int size, bool* result)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < size && ((a[i] !=0) != (b[i] != 0))){
        *result = true;
    }
}

bool gpu_mem_cmp(GpuResource& a, GpuResource& b){
    int size = a.rowCount*a.columnCount;
    return cudaMemcmp((float*)a.resource, (float*)b.resource, size);
}

// Helper function for using CUDA to add vectors in parallel.
bool cudaMemcmp(const float *a, const float* b, int size)
{
    bool* dev_result = nullptr;
    bool result = false;
    int block_count = size/128 + 1;
    dim3 threadsPerBlock(128);

    // Choose which GPU to run on, change this on a multi-GPU system.
    auto cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_result, sizeof(bool));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_result, &result, sizeof(bool), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "Copy false to gpu failed");
        goto Error;
    }

    // Launch a kernel on the GPU with one thread for each element.
    memcmp_kernel<<<block_count, threadsPerBlock>>>(a, b, size, dev_result);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(&result, dev_result, sizeof(bool), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed with message: %d", cudaStatus);
        goto Error;
    }

    cudaFree(dev_result);
    return !result;

Error:
    cudaFree(dev_result);
    
    return false;
}
