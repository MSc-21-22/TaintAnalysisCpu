#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/cfg.h"
#include <memory>
#include "../src/transforms_matrix.h"

std::string convert_to_string(int matrix[], int var_count){
  std::string res;
  for(int i = 0; i<var_count; i++){
    for(int j = 0; j<var_count; j++){
      res += std::to_string(matrix[i*var_count + j]);
    }
    res += " ";
  }
  return res;
}

SCENARIO("matrix transform initilization") {

  GIVEN("an intitlization statment") {
    auto b = std::make_shared<VariableExpression>("b");
    auto taint = std::make_shared<VariableExpression>("£");
    auto exp = std::make_shared<BinaryOperatorExpression>(b,"+",taint);
    InitializerNode<int> node{"int", "a", exp};

    WHEN("transformed to matrix") {
      MatrixTransforms<int> matrixTransformer({"a","b"});
      node.accept(matrixTransformer);

      int correct_matrix[] = {0,1,1,
          0,1,0,
          0,0,1};
      THEN("correct matrix should be: 011 010, 001") {
        auto matrix = matrixTransformer.matrices[0].get();
        CHECK_MESSAGE(std::memcmp(matrix,correct_matrix,9) == 0,
                      convert_to_string(matrix, 3));
      }
    }
  }
} 

SCENARIO("matrix transform assignment") {

  GIVEN("an assignment statment") {
    auto taint = std::make_shared<VariableExpression>("£");
    AssignmentNode<int> node{"a", taint};

    WHEN("transformed to matrix") {
      MatrixTransforms<int> matrixTransformer({"a","b"});
      node.accept(matrixTransformer);

      int correct_matrix[] = 
          {0,0,1,
           0,1,0,
           0,0,1};
      THEN("correct matrix should be: 001 010, 001") {
        auto matrix = matrixTransformer.matrices[0].get();
        CHECK_MESSAGE(std::memcmp(matrix,correct_matrix,9) == 0,
                      convert_to_string(matrix, 3));
      }
    }
  }
} 
