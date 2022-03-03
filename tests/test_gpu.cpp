#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/cfg.h"
#include <memory>
#include "../src/transforms_matrix.h"
#include "../src/matrix_analysis.h"
#include "../src/kernel.h"
#include "../src/cuda/bit_cuda/analysis.h"
#include "../src/cuda/cuda_worklist/analysis.h"

TEST_CASE("bit cuda x=$ -> y=x") {
    std::vector<bit_cuda::Node> nodes;
    std::vector<Transfer> transfer_functions{};

    bit_cuda::Node node1;
    node1.first_transfer_index = 0;
    Transfer& transfer1 = transfer_functions.emplace_back();
    transfer1.x = 1;
    transfer1.rhs[0] = 0;
    nodes.push_back(node1);
    
    bit_cuda::Node node2;
    node2.first_transfer_index = 1;
    Transfer& transfer2 = transfer_functions.emplace_back();
    transfer2.x = 2;
    transfer2.rhs[0] = 1;
    node2.predecessor_index[0] = 0;
    nodes.push_back(node2);

    bit_cuda::execute_analysis(&nodes[0], nodes.size(), &transfer_functions[0], transfer_functions.size());

    CHECK_MESSAGE(nodes[0].data == 3, "First node results doesnt match");
    CHECK_MESSAGE(nodes[1].data == 7, "Second node results doesnt match");
} 

TEST_CASE("worklist cuda x=$ -> y=x") {
    std::vector<cuda_worklist::Node> nodes;
    std::vector<Transfer> transfer_functions{};

    cuda_worklist::Node node1;
    node1.first_transfer_index = 0;
    Transfer& transfer1 = transfer_functions.emplace_back();
    transfer1.x = 1;
    transfer1.rhs[0] = 0;
    nodes.push_back(node1);
    
    cuda_worklist::Node node2;
    node2.first_transfer_index = 1;
    Transfer& transfer2 = transfer_functions.emplace_back();
    transfer2.x = 2;
    transfer2.rhs[0] = 1;
    node2.predecessor_index[0] = 0;
    nodes.push_back(node2);

    cuda_worklist::execute_analysis(&nodes[0], nodes.size(), &transfer_functions[0], transfer_functions.size());

    CHECK_MESSAGE(nodes[0].data == 3, "First node results doesnt match");
    CHECK_MESSAGE(nodes[1].data == 7, "Second node results doesnt match");
} 


TEST_CASE("worklist cuda multi transforms") {
    std::vector<cuda_worklist::Node> nodes;
    std::vector<Transfer> transfers;
    cuda_worklist::Node& node1 = nodes.emplace_back();

    Transfer& transfer1 = transfers.emplace_back();
    node1.first_transfer_index = 0;
    transfer1.x = 1;
    transfer1.rhs[0] = 0;

    Transfer& transfer = transfers.emplace_back();
    transfer.next_transfer_index = 1;
    transfer.x = 2;
    transfer.rhs[0] = 0;

    cuda_worklist::execute_analysis(&nodes[0], nodes.size(), &transfers[0], transfers.size());

    CHECK_MESSAGE(nodes[0].data == 7, "First node results doesnt match");
} 

// TEST_CASE("bit cuda multi transforms") {
//     std::vector<bit_cuda::Node> nodes;
//     std::vector<Transfer> transfers;
//     bit_cuda::Node& node1 = nodes.emplace_back();

//     Transfer& transfer1 = transfers.emplace_back();
//     node1.first_transfer_index = 0;
//     transfer1.x = 1;
//     transfer1.rhs[0] = 0;

//     Transfer& transfer = transfers.emplace_back();
//     transfer.next_transfer_index = 1;
//     transfer.x = 2;
//     transfer.rhs[0] = 0;

//     bit_cuda::execute_analysis(&nodes[0], nodes.size(), &transfers[0], transfers.size());

//     CHECK_MESSAGE(nodes[0].data == 7, "First node results doesnt match");
// } 

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