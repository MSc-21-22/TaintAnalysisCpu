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
    other.rowCount = 0;

    columnCount = other.columnCount;
    other.columnCount = 0;

    resource = other.resource;
    other.resource = nullptr;
}
GpuBoolMatrix& GpuBoolMatrix::operator=(const GpuBoolMatrix& other){
    //Deallocate old resource first
    CHECK(cuBool_Matrix_Free(resource),
        "Failed to deallocate matrix (copy assignment)");

    rowCount = other.rowCount;
    columnCount = other.columnCount;

    CHECK(cuBool_Matrix_Duplicate(other.resource, &resource),
        "Failed to duplicate GPU resource");
    return *this;
}
GpuBoolMatrix& GpuBoolMatrix::operator=(GpuBoolMatrix&& other) noexcept{
    //Deallocate old resource first
    CHECK(cuBool_Matrix_Free(resource),
        "Failed to deallocate matrix (move assignment)");

    rowCount = other.rowCount;
    other.rowCount = 0;

    columnCount = other.columnCount;
    other.columnCount = 0;

    resource = other.resource;
    other.resource = nullptr;
    return *this;
}

BoolMatrix GpuBoolMatrix::retrieve_from_gpu(){
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

// void GpuBoolMatrix::multiply_f32_to_f32(const GpuBoolMatrix& operand, GpuBoolMatrix& result){
//     assert(rowCount == result.rowCount); 
//     assert(operand.columnCount == result.columnCount);
//     assert(columnCount == operand.rowCount);
//     float alpha = 1;
//     float beta = 0;
//     auto status = cublasSgemm_v2(get_cublas(), CUBLAS_OP_N, CUBLAS_OP_N, 
//         rowCount, operand.columnCount, columnCount,
//         &alpha, (float*)resource, rowCount,
//         (float*)operand.resource, operand.rowCount,
//         &beta, (float*)result.resource, result.rowCount);

//     if(status != CUBLAS_STATUS_SUCCESS) {
//         std::cout << "Matrix multiplication failed with " << status << std::endl;
//     }
// }    


// void GpuBoolMatrix::multiply_vector_f32_to_f32(int offset, const GpuBoolMatrix& operand){
//     float* float_resource = (float*)resource;

//     float alpha = 1;
//     float beta = 0;
//     auto status = cublasSgemv_v2(get_cublas(), CUBLAS_OP_N, 
//         operand.rowCount, operand.columnCount,
//         &alpha,
//         (float *)operand.resource, operand.rowCount,
//         float_resource + offset, 1, 
//         &beta, float_resource + offset, 1);

//     if(status != CUBLAS_STATUS_SUCCESS) {
//         std::cout << "Matrix vector multiplication failed with " << status << std::endl;
//     }
// }

GpuBoolMatrix::~GpuBoolMatrix(){
    CHECK(cuBool_Matrix_Free(resource), 
        "Failed to deallocate matrix(deconstruction)");
}