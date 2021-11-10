#pragma once
#include "matrix.h"
#include "bool_matrix.h"
#include <cubool.h>
#include <functional>
#include <ostream>

void create_cubool();
void destroy_cubool();

template<typename OperationType>
class GpuOperation{
    std::function<void(OperationType&)> operation;
public:
    GpuOperation(std::function<void(OperationType&)> f) : operation(f) { }

    void execute(OperationType& result) const{
        operation(result);
    }
};

class GpuBoolMatrix{
public:
    cuBool_Matrix resource;
    int rowCount, columnCount;

    GpuBoolMatrix(int rows, int columns);
    GpuBoolMatrix(const BoolMatrix& matrix);
    GpuBoolMatrix(const GpuBoolMatrix& other);
    GpuBoolMatrix(GpuBoolMatrix&& other) noexcept;
    GpuBoolMatrix& operator=(const GpuBoolMatrix& other);
    GpuBoolMatrix& operator=(GpuBoolMatrix&& other) noexcept;
    GpuBoolMatrix& operator=(const GpuOperation<GpuBoolMatrix>& operation);
    
    GpuOperation<GpuBoolMatrix> operator*(const GpuBoolMatrix& other) const;
    GpuOperation<GpuBoolMatrix> operator+(const GpuBoolMatrix& other) const;

    uint32_t get_element_count() const;

    BoolMatrix retrieve_from_gpu() const;
    ~GpuBoolMatrix();
};

std::ostream& operator<<(std::ostream& os, const GpuBoolMatrix& matrix);