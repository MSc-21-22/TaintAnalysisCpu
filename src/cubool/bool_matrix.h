#pragma once
#include <vector>
#include <assert.h>
#include <cstdint>
#include <ostream>

class BoolMatrix{
public:
    std::vector<uint32_t> rows;
    std::vector<uint32_t> columns;
    int row_count, column_count;

    BoolMatrix(int row_count, int column_count) : row_count(row_count), column_count(column_count) {}
    BoolMatrix(int row_count, int column_count, std::vector<uint32_t>&& rows, std::vector<uint32_t>&& columns) : rows(rows), columns(columns), row_count(row_count), column_count(column_count) {}
    
    bool operator==(const BoolMatrix& other);

    void add_safe(int row_index, int column_index);
    void add(int row_index, int column_index);
};

std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix);

BoolMatrix initial_matrix(int var_count, int node_count);
