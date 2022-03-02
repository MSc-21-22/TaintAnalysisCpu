#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/cfg.h"
#include "../src/cuda_worklist/cuda_worklist_transformer.h"
#include "../src/transforms_matrix.h"

TEST_CASE("unit matrix") {

    auto matrix = unit_matrix<float>(4);

    
    //     1,0,0,0,
    //     0,1,0,0,
    //     0,0,1,0,
    //     0,0,0,1
    float correct_matrix[] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1};
    CHECK_MESSAGE(std::memcmp(matrix.matrix.get(), correct_matrix, sizeof(correct_matrix)) == 0,
                matrix.to_string());

}

TEST_CASE("matrix transform initilization") {

    auto b = std::make_shared<VariableExpression>("b");
    auto taint = std::make_shared<VariableExpression>(TAINT_VAR);
    auto exp = std::make_shared<BinaryOperatorExpression>(b,"+",taint);
    AssignmentNode<int> node("a", exp);

    MatrixTransforms<int,float> matrixTransformer({"a","b"});
    node.accept(matrixTransformer);

    
    //     0,1,0,1,
    //     0,1,0,0,
    //     0,0,1,0,
    //     0,0,0,1
    float correct_matrix[] = {
        0,0,0,0,
        1,1,0,0,
        0,0,1,0,
        1,0,0,1};
    Matrix<float> matrix = matrixTransformer.matrices[0];
    CHECK_MESSAGE(std::memcmp(matrix.matrix.get(), correct_matrix, sizeof(correct_matrix)) == 0,
                matrix.to_string());

} 

TEST_CASE("matrix transform assignment") {

    auto taint = std::make_shared<VariableExpression>(TAINT_VAR);
    AssignmentNode<int> node{"a", taint};

    MatrixTransforms<int, float> matrixTransformer({"a","b"});
    node.accept(matrixTransformer);


    //      0,0,0,1,
    //      0,1,0,0,
    //      0,0,1,0,
    //      0,0,0,1
    float correct_matrix[] = 
       {0,0,0,0,
        0,1,0,0,
        0,0,1,0,
        1,0,0,1};

      Matrix<float> matrix = matrixTransformer.matrices[0];
      CHECK_MESSAGE(std::memcmp(matrix.matrix.get(),correct_matrix,sizeof(correct_matrix)) == 0,
                    matrix.to_string());
} 

TEST_CASE("matrix transform assign return") {

    AssignReturnNode<int> node{"a"};

    MatrixTransforms<int, float> matrixTransformer({"a","b"});
    node.accept(matrixTransformer);

    //      0,0,1,0,
    //      0,1,0,0,
    //      0,0,0,0,
    //      0,0,0,1
    float correct_matrix[] = 
        {0,0,0,0,
         0,1,0,0,
         1,0,0,0,
         0,0,0,1};

      Matrix<float> matrix = matrixTransformer.matrices[0];
      CHECK_MESSAGE(std::memcmp(matrix.matrix.get(),correct_matrix,sizeof(correct_matrix)) == 0,
                    matrix.to_string());
} 

TEST_CASE("matrix transform function entry"){

    auto c = std::make_shared<VariableExpression>("c");
    auto taint = std::make_shared<VariableExpression>(TAINT_VAR);

    std::vector<std::shared_ptr<Expression>> args{c,taint};
    std::string taint_var(TAINT_VAR);
    auto funcCall = std::make_shared<PropagationNode<int>>("f(c, "+ taint_var +")");
    std::vector<std::string> params{"a","b"};
    auto funcEntry = std::make_shared<FunctionEntryNode<int>>("f", params);
    funcEntry->arguments = args;
    auto funcDef = std::make_shared<PropagationNode<int>>("void f(int a, int b)");
    
    funcCall->successors.insert(funcEntry);
    funcEntry->predecessors.insert(funcCall);
    funcEntry->successors.insert(funcDef);
    funcDef->predecessors.insert(funcEntry);

    MatrixTransforms<int,float> matrixTransforms({"a","b","c"});
    funcEntry->accept(matrixTransforms);

    //     {0,0,1,0,0,
    //      0,0,0,0,1,
    //      0,0,0,0,0,
    //      0,0,0,0,0,
    //      0,0,0,0,1
    float  correct_matrix[] =
        {0,0,0,0,0,
         0,0,0,0,0,
         1,0,0,0,0,
         0,0,0,0,0,
         0,1,0,0,1};

    Matrix<float> matrix = matrixTransforms.matrices[0];
    CHECK_MESSAGE(std::memcmp(matrix.matrix.get(),correct_matrix,sizeof(correct_matrix)) == 0,
                  matrix.to_string());
}

TEST_CASE("matrix transform return") {

    auto a = std::make_shared<VariableExpression>("a");
    ReturnNode<int> node(a, "f");

    MatrixTransforms<int, float> matrixTransformer({"a","b"});
    node.accept(matrixTransformer);

    //      0,0,0,0,
    //      0,0,0,0,
    //      1,0,0,0,
    //      0,0,0,1
    float  correct_matrix[] = 
        {0,0,1,0,
         0,0,0,0,
         0,0,0,0,
         0,0,0,1};

      Matrix<float> matrix = matrixTransformer.matrices[0];
      CHECK_MESSAGE(std::memcmp(matrix.matrix.get(),correct_matrix,sizeof(correct_matrix)) == 0,
                    matrix.to_string());
}

TEST_CASE("Create successor node matrix"){
    auto node1 = std::make_shared<PropagationNode<int>>("Empty");
    auto node2 = std::make_shared<PropagationNode<int>>("Empty");
    auto node3 = std::make_shared<PropagationNode<int>>("Empty");

    node1->successors.insert({node2,node3});
    node2->successors.insert(node3);
    node2->predecessors.insert(node1);
    node3->predecessors.insert({node1,node2});
    
    std::vector<std::shared_ptr<Node<int>>> vec{node1,node2,node3};
    auto matrix = get_successor_matrix<int, float>(vec);

    //     1,1,1,
    //     0,1,1,
    //     0,0,1
    float correct_matrix[] = {
        1,0,0,
        1,1,0,
        1,1,1};
      CHECK_MESSAGE(std::memcmp(matrix.matrix.get(), correct_matrix, sizeof(correct_matrix)) == 0,
                    matrix.to_string());
}
