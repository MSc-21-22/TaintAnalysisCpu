#include "digraph.h"

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Expression>& arg){
    os << arg->dotPrint();
    return os;
}