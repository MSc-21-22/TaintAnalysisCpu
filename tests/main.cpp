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

    MatrixTransforms<int> matrixTransformer({"a","b"});
    node.accept(matrixTransformer);

    int correct_matrix[] = {
        0,1,0,1,
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
        {0,0,0,1,
         0,1,0,0,
         0,0,1,0,
         0,0,0,1};

      Matrix matrix = matrixTransformer.matrices[0];
      CHECK_MESSAGE(std::memcmp(matrix.matrix.get(),correct_matrix,16) == 0,
                    matrix.to_string());
} 

TEST_CASE("matrix transform function entry"){

    auto c = std::make_shared<VariableExpression>("c");
    auto taint = std::make_shared<VariableExpression>("£");

    std::vector<std::shared_ptr<Expression>> args{c,taint};
    auto funcCall = std::make_shared<FunctionCall<int>>("f", args);
    std::vector<std::string> params{"a","b"};
    auto funcEntry = std::make_shared<FunctionEntryNode<int>>();
    auto funcDef = std::make_shared<FunctionDefinition<int>>("f", params);
    
    funcCall->successors.insert(funcEntry);
    funcEntry->predecessors.insert(funcCall);
    funcEntry->successors.insert(funcDef);
    funcDef->predecessors.insert(funcEntry);

    MatrixTransforms<int> matrixTransforms({"a","b","c"});
    funcEntry->accept(matrixTransforms);

    int correct_matrix[] =
        {0,0,1,0,0,
         0,0,0,0,1,
         0,0,0,0,0,
         0,0,0,0,0,
         0,0,0,0,1};

    Matrix matrix = matrixTransforms.matrices[0];
    CHECK_MESSAGE(std::memcmp(matrix.matrix.get(),correct_matrix,16) == 0,
                  matrix.to_string());
}
