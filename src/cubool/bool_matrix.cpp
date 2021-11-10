#include "bool_matrix.h"

void BoolMatrix::add_safe(int row_index, int column_index){
    if(rows.size() == 0){
        add(row_index, column_index);
    }else{
        if(rows.back() > row_index){
            assert(false);
        }else{
            if(rows.back() == row_index && columns.back() > column_index){
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

std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix){
    auto row_it = matrix.rows.begin();
    auto column_it = matrix.columns.begin();
    int elements_left = matrix.rows.size();
    os << '\n';
    for(int row = 0; row < matrix.row_count; ++row){
        for(int column = 0; column < matrix.column_count; ++column){
            if(elements_left > 0 && row == *row_it && column == *column_it){
                os << '1';
                elements_left--;
                row_it++;
                column_it++;
            }else{
                os << '0';
            }
            os << ' ';
        }
            os << '\n';
    }
}