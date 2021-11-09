#pragma once
#include "matrix.h"
#include "bool_matrix.h"
#include <cubool.h>

void create_cubool();
void destroy_cubool();

class GpuBoolMatrix{
public:
    cuBool_Matrix resource;
    int rowCount, columnCount;

    GpuBoolMatrix(const BoolMatrix& matrix);
    GpuBoolMatrix(const GpuBoolMatrix& other);
    GpuBoolMatrix(GpuBoolMatrix&& other) noexcept;
    GpuBoolMatrix& operator=(const GpuBoolMatrix& other);
    GpuBoolMatrix& operator=(GpuBoolMatrix&& other) noexcept;

    // void multiply_f32_to_f32(const GpuBoolMatrix& operand, GpuBoolMatrix& result);
    // void multiply_vector_f32_to_f32(int offset, const GpuBoolMatrix& operand);

    BoolMatrix retrieve_from_gpu();
    ~GpuBoolMatrix();
};