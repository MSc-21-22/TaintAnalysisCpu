#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cfg/cfg.h>
#include <cuda/cuda_transformer.h>
#include <cfg/transformations/transforms_matrix.h>
#include <iostream>

TEST_CASE("cuda multiple transferfunctions"){
    std::cout << "Hello world" <<  std::endl;

    std::vector<std::string> parameters = {"a", "b", "c"};
    std::vector<int> parameter_indexes = {3, 4, 5};

    auto i = std::make_shared<VariableExpression>("i");
    i->var_index = 0;
    auto j = std::make_shared<VariableExpression>("j");
    j->var_index = 1;
    auto h = std::make_shared<VariableExpression>("h");
    h->var_index = 2;
    std::vector<std::shared_ptr<Expression>> arguments = {i,j,h};

    auto funcEntry = std::make_shared<FunctionEntryNode>("f", parameters);
    funcEntry->arguments = arguments;
    funcEntry->formal_parameter_indexes = parameter_indexes;

    std::vector<std::shared_ptr<Node>> nodes = {funcEntry};
    CudaTransformer<bit_cuda::Node> transformer = transform_bit_cuda(nodes);

    CHECK_MESSAGE(transformer.transfer_functions.size() == 3, "Function entry should have 3 transfer functions");
    CHECK_MESSAGE(transformer.nodes[0].first_transfer_index == 0, "first transfer_index of node should be 0");
    CHECK_MESSAGE(transformer.transfer_functions[0].next_transfer_index == 1, "transfer_functions[0].next_transfer_index should be 1");
    CHECK_MESSAGE(transformer.transfer_functions[1].next_transfer_index == 2, "transfer_functions[1].next_transfer_index should be 2");

}

TEST_CASE("cuda-worklist transforms successor"){
    auto funcCall = std::make_shared<PropagationNode>("f()");
    auto funcEntry = std::make_shared<PropagationNode>("f");
    auto funcDef = std::make_shared<PropagationNode>("void f(int a, int b)");
    
    funcCall->add_successor(funcEntry);
    funcEntry->add_predecessor(funcCall);
    funcEntry->add_successor(funcDef);
    funcDef->add_predecessor(funcEntry);

    std::vector<std::shared_ptr<Node>> nodes = {funcCall, funcEntry, funcDef};
    CudaTransformer<cuda_worklist::Node> transformer = transform_cuda_worklist(nodes);

    CHECK_MESSAGE(transformer.nodes[0].successor_index[0] == 1, "Function call should have function entry as successor");
    CHECK_MESSAGE(transformer.nodes[1].successor_index[0] == 2, "Function entry should have function definition as successor");
}

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
    AssignmentNode node("a", exp);

    MatrixTransforms<float> matrixTransformer({"a","b"});
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
    AssignmentNode node{"a", taint};

    MatrixTransforms<float> matrixTransformer({"a","b"});
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

    AssignReturnNode node{"a"};

    MatrixTransforms<float> matrixTransformer({"a","b"});
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
    auto funcCall = std::make_shared<PropagationNode>("f(c, "+ taint_var +")");
    std::vector<std::string> params{"a","b"};
    auto funcEntry = std::make_shared<FunctionEntryNode>("f", params);
    funcEntry->arguments = args;
    auto funcDef = std::make_shared<PropagationNode>("void f(int a, int b)");
    
    funcCall->add_successor(funcEntry);
    funcEntry->add_predecessor(funcCall);
    funcEntry->add_successor(funcDef);
    funcDef->add_predecessor(funcEntry);

    MatrixTransforms<float> matrixTransforms({"a","b","c"});
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
    ReturnNode node(a, "f");

    MatrixTransforms<float> matrixTransformer({"a","b"});
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
    auto node1 = std::make_shared<PropagationNode>("Empty");
    auto node2 = std::make_shared<PropagationNode>("Empty");
    auto node3 = std::make_shared<PropagationNode>("Empty");

    node1->add_successor(node2);
    node1->add_successor(node3);
    node2->add_successor(node3);
    node2->add_predecessor(node1);
    node3->add_predecessor(node1);
    node3->add_predecessor(node2);
    
    std::vector<std::shared_ptr<Node>> vec{node1,node2,node3};
    auto matrix = get_successor_matrix<float>(vec);

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
