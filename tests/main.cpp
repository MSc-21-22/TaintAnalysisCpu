#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/cfg.h"
#include <memory>
#include "../src/transforms_matrix.h"

TEST_CASE("matrix transform initilization") {

    auto b = std::make_shared<VariableExpression>("b");
    auto taint = std::make_shared<VariableExpression>("£");
    auto exp = std::make_shared<BinaryOperatorExpression>(b,"+",taint);
    InitializerNode<int> node("int", "a", exp);

    dumdum();
    MatrixTransforms<int> matrixTransformer({"a","b"});
    node.accept(matrixTransformer);

    int correct_matrix[] = {
        0,1,1,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1};
      Matrix matrix = matrixTransformer.matrices[0];
      CHECK_MESSAGE(std::memcmp(matrix.matrix.get(), correct_matrix, 16) == 0,
                    matrix.to_string());

} 

TEST_CASE("matrix transform assignment") {

    auto taint = std::make_shared<VariableExpression>("£");
    AssignmentNode<int> node{"a", taint};

    MatrixTransforms<int> matrixTransformer({"a","b"});
    node.accept(matrixTransformer);

    int correct_matrix[] = 
        {0,0,1,0,
          0,1,0,0,
          0,0,1,0,
          0,0,0,1};

      Matrix matrix = matrixTransformer.matrices[0];
      CHECK_MESSAGE(std::memcmp(matrix.matrix.get(),correct_matrix,16) == 0,
                    matrix.to_string());
} 
