#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/cfg.h"
#include <memory>
#include "../src/transforms_matrix.h"
#include "../src/matrix_analysis.h"
#include "../src/kernel.h"
#include "../src/bit_cuda/analysis.h"



TEST_CASE("bit cuda x=$ -> y=x") {
    std::vector<bit_cuda::Node> nodes;
    std::vector<bit_cuda::Transfer> transfer_functions{};

    bit_cuda::Node node1;
    node1.first_transfer_index = 0;
    bit_cuda::Transfer& transfer1 = transfer_functions.emplace_back();
    transfer1.x = 1;
    transfer1.rhs[0] = 0;
    transfer1.rhs[1] = -1;
    node1.predecessor_index[0] = -1;
    nodes.push_back(node1);
    
    bit_cuda::Node node2;
    node2.first_transfer_index = 1;
    bit_cuda::Transfer& transfer2 = transfer_functions.emplace_back();
    transfer2.x = 2;
    transfer2.rhs[0] = 1;
    transfer2.rhs[1] = -1;
    node2.predecessor_index[0] = 0;
    node2.predecessor_index[1] = -1;
    nodes.push_back(node2);

    bit_cuda::execute_analysis(&nodes[0], nodes.size(), &transfer_functions[0], transfer_functions.size());

    CHECK_MESSAGE(nodes[0].data.data == 3, "First node results doesnt match");
    CHECK_MESSAGE(nodes[1].data.data == 7, "Second node results doesnt match");
} 

TEST_CASE("bit cuda multi transforms") {
    std::vector<bit_cuda::Node> nodes;
    std::vector<bit_cuda::Transfer> transfers;
    bit_cuda::Node& node1 = nodes.emplace_back();

    bit_cuda::Transfer& transfer1 = transfers.emplace_back();
    node1.first_transfer_index = 0;
    transfer1.x = 1;
    transfer1.rhs[0] = 0;
    transfer1.rhs[1] = -1;
    node1.predecessor_index[0] = -1;

    bit_cuda::Transfer& transfer = transfers.emplace_back();
    transfer.next_transfer_index = 1;
    transfer.x = 2;
    transfer.rhs[0] = 0;

    bit_cuda::execute_analysis(&nodes[0], nodes.size(), &transfers[0], transfers.size());

    CHECK_MESSAGE(nodes[0].data.data == 7, "First node results doesnt match");
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

TEST_CASE("Matrix copying test"){
    create_cublas();

    Matrix<float> matrixA{2};
    matrixA(0,0) = 1;
    matrixA(1,1) = 1;
    GpuMatrix a{matrixA};
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
    
    GpuMatrix a{matrixA};
    GpuMatrix b{matrixB};
    GpuMatrix c(matrixA.rowCount, matrixB.columnCount);
    a.multiply(b, c);
    
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
    GpuMatrix a{matrixA};

    Matrix<float> matrixB = unit_matrix<float>(2);
    matrixB(0,1) = 1;
    GpuMatrix b{matrixB};

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
    GpuMatrix succ_gpu{succ};

    Matrix<float> state(5,2);
    state(3,0) = 1;
    state(3,1) = 1;
    state(0,0) = 1;
    GpuMatrix state_gpu{state};

    assert(sizeof(float) == 4);
    
    GpuMatrix c(state_gpu.resource.rowCount, succ_gpu.resource.columnCount);
    state_gpu.multiply(succ_gpu, c);
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
    GpuMatrix a{matrixA};
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
    GpuMatrix b{matrixB};
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
    
    GpuMatrix c(a.resource.rowCount, b.resource.columnCount);
    a.multiply(b, c);
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
    // a = $
    // b = a
    create_cublas();
    // 0, 0, 0, 1
    // 0, 1, 0, 0
    // 0, 0, 1, 0
    // 0, 0, 0, 1
    Matrix<float> assign_a = unit_matrix<float>(4);
    assign_a(0,0) = 0;
    assign_a(0,3) = 1;
    GpuMatrix transfer = assign_a;

    // 0, 0
    // 0, 0
    // 0, 0
    // 1, 1
    Matrix<float> state(4,2);
    state(3,0) = 1;
    state(3,1) = 1;
    GpuMatrix state_gpu = state;

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
    // a = $
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
    GpuMatrix correct_matrix(correct_state, 4, 2);

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

    GpuMatrix a(test_matrix);
    GpuMatrix b(test_matrix);


    CHECK_MESSAGE(gpu_mem_cmp(a.resource, b.resource),
            "Two gpu matricies were not identical on the host device");
}