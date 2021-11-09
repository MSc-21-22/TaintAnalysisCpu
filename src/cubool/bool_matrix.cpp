#include "bool_matrix.h"

void BoolMatrix::add_safe(int row_index, int column_index){
    if(rows.size() == 0){
        add(row_index, column_index);
    }else{
        if(rows.back() > row_index){
            assert(false);
        }else{
            if(columns.back() > column_index){
                assert(false);
            }else{
                add(row_index, column_index);
            }
        }
    }
}

void BoolMatrix::add(int row_index, int column_index){
    rows.push_back(row_index);
    columns.push_back(column_index);
}

bool BoolMatrix::operator==(const BoolMatrix& other){
    return row_count == other.row_count &&
        column_count == other.column_count &&
        rows == other.rows &&
        columns == other.columns;
}