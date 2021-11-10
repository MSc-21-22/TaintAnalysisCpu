#include <cublas.h>
#include <iostream>
#include <assert.h>
#include "GpuBoolMatrix.h"
#include <cubool.h>
#include "bool_matrix.h"

#define CHECK(f, err) { cuBool_Status s = f; if (s != CUBOOL_STATUS_SUCCESS) { std::cout << err << ": " << s << '\n'; assert(false); } }    

static bool is_initialized = false;

void create_cubool(){
    if(is_initialized){
        return;
    }

    CHECK(cuBool_Initialize(CUBOOL_HINT_NO),
        "Failed to initialize cubool");
    is_initialized = true;
}
void destroy_cubool(){
    if(!is_initialized){
        return;
    }

    cuBool_Finalize();
    is_initialized = false;
}

GpuBoolMatrix::GpuBoolMatrix(int rows, int columns){
    rowCount = rows;
    columnCount = columns;

    CHECK(cuBool_Matrix_New(&resource, rows, columns),
        "Failed to allocate matrix");
}

GpuBoolMatrix::GpuBoolMatrix(const BoolMatrix& matrix){
    rowCount = matrix.row_count;
    columnCount = matrix.column_count;
    
    auto* rows_ptr = (cuBool_Index*)&*matrix.rows.begin();
    auto* columns_ptr = (cuBool_Index*)&*matrix.columns.begin();

    CHECK(cuBool_Matrix_New(&resource, matrix.row_count, matrix.column_count),
        "Failed to allocate matrix");
    CHECK(cuBool_Matrix_Build(resource, rows_ptr, columns_ptr, matrix.rows.size(), CUBOOL_HINT_VALUES_SORTED),
        "Failed to copy matrix to GPU");
}

GpuBoolMatrix::GpuBoolMatrix(const GpuBoolMatrix& other){
    rowCount = other.rowCount;
    columnCount = other.columnCount;

    CHECK(cuBool_Matrix_Duplicate(other.resource, &resource),
        "Failed to duplicate GPU resource");
}
GpuBoolMatrix::GpuBoolMatrix(GpuBoolMatrix&& other) noexcept{
    rowCount = other.rowCount;
    columnCount = other.columnCount;
    resource = other.resource;

    other.resource = nullptr;
}
GpuBoolMatrix& GpuBoolMatrix::operator=(const GpuBoolMatrix& other){
    //Deallocate old resource 
    if(resource != nullptr){
        CHECK(cuBool_Matrix_Free(resource),
            "Failed to deallocate matrix (copy assignment)");
    }

    rowCount = other.rowCount;
    columnCount = other.columnCount;

    CHECK(cuBool_Matrix_Duplicate(other.resource, &resource),
        "Failed to duplicate GPU resource");
    return *this;
}
GpuBoolMatrix& GpuBoolMatrix::operator=(GpuBoolMatrix&& other) noexcept{
    std::swap(rowCount, other.rowCount);
    std::swap(columnCount, other.columnCount);
    std::swap(resource, other.resource);
    return *this;
}

GpuBoolMatrix& GpuBoolMatrix::operator=(const GpuOperation<GpuBoolMatrix>& operation){
    operation.execute(*this);
    return *this;
}

BoolMatrix GpuBoolMatrix::retrieve_from_gpu() const{
    cuBool_Index values;
    CHECK(cuBool_Matrix_Nvals(resource, &values),
        "Failed to get number of values");

    uint32_t rows[4096];
    uint32_t columns[4096];

    CHECK(cuBool_Matrix_ExtractPairs(resource, rows, columns, &values),
        "Failed to retrieve data from GPU");

    std::vector<uint32_t> row_vec;
    row_vec.assign(rows, rows+values);
    std::vector<uint32_t> column_vec;
    column_vec.assign(columns, columns+values);
    return BoolMatrix(rowCount, columnCount, std::move(row_vec), std::move(column_vec));
}

GpuOperation<GpuBoolMatrix> GpuBoolMatrix::operator*(const GpuBoolMatrix& other) const{
    GpuOperation<GpuBoolMatrix> op(
        [=](GpuBoolMatrix& result){
            assert(result.columnCount == other.columnCount);
            assert(result.rowCount == rowCount);
            assert(columnCount == other.rowCount);

            CHECK(cuBool_MxM(result.resource, resource, other.resource, CUBOOL_HINT_NO),
                "Failed to do matrix multiplication");
        }
    );
    return op;
}

GpuOperation<GpuBoolMatrix> GpuBoolMatrix::operator+(const GpuBoolMatrix& other) const{
    GpuOperation<GpuBoolMatrix> op(
        [=](GpuBoolMatrix& result){
            assert(result.rowCount == other.rowCount);
            assert(result.rowCount == rowCount);

            assert(result.columnCount == other.columnCount);
            assert(result.columnCount == columnCount);
            

            CHECK(cuBool_Matrix_EWiseAdd(result.resource, resource, other.resource, CUBOOL_HINT_NO),
                "Failed to do matrix addition");
        }
    );
    return op;
}

uint32_t GpuBoolMatrix::get_element_count() const{
    cuBool_Index values;
    CHECK(cuBool_Matrix_Nvals(resource, &values),
        "Failed to get number of values");
    return values;
}

GpuBoolMatrix::~GpuBoolMatrix(){
    if(resource != nullptr){
        CHECK(cuBool_Matrix_Free(resource), 
            "Failed to deallocate matrix(deconstruction)");
    }
}