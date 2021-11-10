#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/cfg.h"
#include <memory>
#include "../src/transforms_matrix.h"
#include "../src/matrix_analysis.h"
#include "../src/kernel.h"

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
    auto taint = std::make_shared<VariableExpression>("£");
    auto exp = std::make_shared<BinaryOperatorExpression>(b,"+",taint);
    InitializerNode<int> node("int", "a", exp);

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

    auto taint = std::make_shared<VariableExpression>("£");
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
    auto node1 = std::make_shared<FunctionExitNode<int>>();
    auto node2 = std::make_shared<FunctionExitNode<int>>();
    auto node3 = std::make_shared<FunctionExitNode<int>>();

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

TEST_CASE("Matrix copying test"){
    create_cublas();

    Matrix<float> matrixA{2};
    matrixA(0,0) = 1;
    matrixA(1,1) = 1;
    GpuMatrix<float> a{matrixA};
    Matrix<float> matrixC = a.to_matrix();

    float correct_matrix[] {
        1,0,
        0,1};
    
    destroy_cublas();

    CHECK_MESSAGE(std::memcmp(matrixC.matrix.get(), correct_matrix, sizeof(correct_matrix)) == 0,
            matrixC.to_string());
}

TEST_CASE("Matrix multiply test"){
    create_cublas();

    Matrix<float> matrixA{2};
    matrixA(0,0) = 1;
    matrixA(1,1) = 1;

    Matrix<float> matrixB = unit_matrix<float>(2);
    matrixB(0,1) = 1;
    matrixB(1,1) = 1;

    assert(sizeof(float) == 4);
    
    GpuMatrix<float> a{matrixA};
    GpuMatrix<float> b{matrixB};
    GpuMatrix<float> c = a.multiply(b);
    
    Matrix<float> matrixC = c.to_matrix();

    float correct_matrix[] {
        1,0,
        1,1};
    
    destroy_cublas();

    CHECK_MESSAGE(std::memcmp(matrixC.matrix.get(), correct_matrix, sizeof(correct_matrix)) == 0,
            matrixC.to_string());
}

TEST_CASE("Matrix vector multiply test"){
    create_cublas();

    Matrix<float> matrixA{2};
    matrixA(0,0) = 1;
    GpuMatrix<float> a{matrixA};

    Matrix<float> matrixB = unit_matrix<float>(2);
    matrixB(0,1) = 1;
    GpuMatrix<float> b{matrixB};

    assert(sizeof(float) == 4);
    
    b.multiply_vector(1, a);
    Matrix<float> matrixC = b.to_matrix();

    // 1,1
    // 0,0
    float correct_matrix[] {
        1,0,
        1,0};
    
    destroy_cublas();

    CHECK_MESSAGE(std::memcmp(matrixC.matrix.get(), correct_matrix, sizeof(correct_matrix)) == 0,
            matrixC.to_string());
}

TEST_CASE("Matrix multiply initial state with succ test"){
    create_cublas();

    Matrix<float> succ = unit_matrix<float>(2);
    succ(0,1) = 1;
    GpuMatrix<float> succ_gpu{succ};

    Matrix<float> state(5,2);
    state(3,0) = 1;
    state(3,1) = 1;
    state(0,0) = 1;
    GpuMatrix<float> state_gpu{state};

    assert(sizeof(float) == 4);
    
    auto c = state_gpu.multiply(succ_gpu);
    Matrix<float> matrixC = c.to_matrix();

    // 1 1
    // 0 0
    // 0 0
    // 1 1
    // 0 0

    float correct_matrix[] {
        1,0,0,1,0,
        1,0,0,2,0};
    
    destroy_cublas();

    CHECK_MESSAGE(std::memcmp(matrixC.matrix.get(), correct_matrix, sizeof(correct_matrix)) == 0,
            matrixC.to_string());
}


TEST_CASE("Matrix multiply 5x5"){
    create_cublas();

    Matrix<float> matrixA{5};
    matrixA(0,0) = 1;
    matrixA(1,1) = 1;
    matrixA(1,2) = 1;
    matrixA(3,0) = 1;
    matrixA(3,2) = 1;
    matrixA(3,4) = 1;
    matrixA(4,3) = 1;
    GpuMatrix<float> a{matrixA};
    auto test_a = a.to_matrix();

    float correct_a[] = {
        1,0,0,1,0,
        0,1,0,0,0,
        0,1,0,1,0,
        0,0,0,0,1,
        0,0,0,1,0
    };

    CHECK_MESSAGE(std::memcmp(test_a.matrix.get(), correct_a, sizeof(correct_a)) == 0,
        test_a.to_string());

    Matrix<float> matrixB = unit_matrix<float>(5);
    matrixB(3,1) = 1;
    GpuMatrix<float> b{matrixB};
    auto test_b = b.to_matrix();

    float correct_b[] = {
        1,0,0,0,0,
        0,1,0,1,0,
        0,0,1,0,0,
        0,0,0,1,0,
        0,0,0,0,1
    };

    CHECK_MESSAGE(std::memcmp(test_b.matrix.get(), correct_b, sizeof(correct_b)) == 0,
            test_b.to_string());

    assert(sizeof(float) == 4);
    
    auto c = a.multiply(b);
    Matrix<float> matrixC = c.to_matrix();

    // 1 0 0 0 0
    // 0 1 1 0 0
    // 0 0 0 0 0
    // 1 0 1 0 1
    // 0 1 0 1 0

    float correct_matrix[] {
        1, 0, 0, 1, 0,
        0, 1, 0, 0, 1,
        0, 1, 0, 1, 0,
        0, 0, 0, 0, 1,
        0, 0, 0, 1, 0};
    
    destroy_cublas();

    CHECK_MESSAGE(std::memcmp(matrixC.matrix.get(), correct_matrix, sizeof(correct_matrix)) == 0,
            matrixC.to_string());
}

TEST_CASE("Matrix vector multiplication error 13 reproduction"){
    // a = £
    // b = a
    create_cublas();
    // 0, 0, 0, 1
    // 0, 1, 0, 0
    // 0, 0, 1, 0
    // 0, 0, 0, 1
    Matrix<float> assign_a = unit_matrix<float>(4);
    assign_a(0,0) = 0;
    assign_a(0,3) = 1;
    GpuMatrix<float> transfer = assign_a;

    // 0, 0
    // 0, 0
    // 0, 0
    // 1, 1
    Matrix<float> state(4,2);
    state(3,0) = 1;
    state(3,1) = 1;
    GpuMatrix<float> state_gpu = state;

    state_gpu.multiply_vector(0, transfer);


    Matrix<float> result = state_gpu.to_matrix(); 
    //     1,0,
    //     0,0,
    //     0,0,
    //     1,1
    float correct_state[] = {
        1,0,0,1,
        0,0,0,1};

    destroy_cublas();
    CHECK_MESSAGE(std::memcmp(result.matrix.get(), correct_state, sizeof(correct_state)) == 0,
            result.to_string());
}

TEST_CASE("Run analysis"){
    // a = £
    // b = a

    Matrix<float> succ = unit_matrix<float>(2);
    succ(0,1) = 1;

    // 0, 0, 0, 1
    // 0, 1, 0, 0
    // 0, 0, 1, 0
    // 0, 0, 0, 1
    Matrix<float> assign_a = unit_matrix<float>(4);
    assign_a(0,0) = 0;
    assign_a(0,3) = 1;

    Matrix<float> assign_b = unit_matrix<float>(4);
    assign_b(1,1) = 0;
    assign_b(1,0) = 1;

    // 0, 0
    // 0, 0
    // 0, 0
    // 1, 1
    Matrix<float> state(4,2);
    state(3,0) = 1;
    state(3,1) = 1;

    std::vector<Matrix<float>> transfer_matrices = {assign_a, assign_b};
    auto result = analyse(transfer_matrices, succ, state);

    //     1,1,
    //     0,1,
    //     0,0,
    //     1,1
    float correct_state[] = {
        1,0,0,1,
        1,1,0,1};
    GpuMatrix<float> correct_matrix(correct_state, 4, 2);

    CHECK_MESSAGE(gpu_mem_cmp(result.resource, correct_matrix.resource),
            result.to_matrix().to_string());
}

TEST_CASE("Gpu memcmp"){


    // 0, 0, 0, 1
    // 0, 1, 0, 0
    // 0, 0, 1, 0
    // 0, 0, 0, 1
    Matrix<float> test_matrix = unit_matrix<float>(4);
    test_matrix(0,0) = 0;
    test_matrix(0,3) = 1;

    GpuMatrix<float> a(test_matrix);
    GpuMatrix<float> b(test_matrix);


    CHECK_MESSAGE(gpu_mem_cmp(a.resource, b.resource),
            "Two gpu matricies were not identical on the host device");
}

#include <cubool/bool_matrix.h>
#include <cubool/GpuBoolMatrix.h>

TEST_CASE("test cubool"){
    BoolMatrix matrix(3,3);
    matrix.add_safe(0,0);
    matrix.add_safe(1,1);
    matrix.add_safe(2,2);

    BoolMatrix matrix_2(3,3);
    matrix_2.add_safe(0,0);
    matrix_2.add_safe(0,1);
    matrix_2.add_safe(1,2);

    create_cubool();

    //Enclose in seperate scope to ensure gpu deallocation
    //before destroy_cubool to avoid exception
    {

        GpuBoolMatrix a(matrix);
        GpuBoolMatrix b(a);

        CHECK_MESSAGE(a.resource != b.resource, "The gpu pointers should be different");

        auto a_m = a.retrieve_from_gpu();
        auto b_m = b.retrieve_from_gpu();

        CHECK_MESSAGE(matrix == a_m, "a_m should be equal to the initial matrix");
        CHECK_MESSAGE(a_m == b_m, "The copied matrix should be equal to the new matrix");
    

        GpuBoolMatrix other(matrix_2);
        GpuBoolMatrix result(3,3);
        result = a * other;

        auto result_m = result.retrieve_from_gpu();

        CHECK_MESSAGE(matrix_2 == result_m, "Multiplication with unit matrix cause no change");
    }

    destroy_cubool();
}

TEST_CASE("cubool addition bug"){
    BoolMatrix matrix(3,3);
    matrix.add_safe(0,0);

    BoolMatrix matrix_2(3,3);
    matrix_2.add_safe(1,0);

    create_cubool();

    //Enclose in seperate scope to ensure gpu deallocation
    //before destroy_cubool to avoid exception
    {
        GpuBoolMatrix a(matrix);
        GpuBoolMatrix c(matrix_2);

        GpuBoolMatrix r(a);
        a = r + c;
    }

    destroy_cubool();
}