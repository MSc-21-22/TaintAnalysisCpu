#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <memory>
#include <cuda/bit_cuda/analysis.h>
#include <cuda/cuda_worklist/analysis.h>
#include <base_taint_analysis.h>


TEST_CASE("bit cuda x=$ -> y=x") {
    DynamicArray<taint::Node> nodes(2, sizeof(taint::Node));
    std::vector<Transfer> transfer_functions{};

    taint::Node node1;
    node1.first_transfer_index = 0;
    Transfer& transfer1 = transfer_functions.emplace_back();
    transfer1.var_index = 1;
    transfer1.rhs |= 1;
    nodes.emplace_back(node1);
    
    taint::Node node2;
    node2.first_transfer_index = 1;
    Transfer& transfer2 = transfer_functions.emplace_back();
    transfer2.var_index = 2;
    transfer2.rhs |= 2;
    node2.predecessor_index[0] = 0;
    nodes.emplace_back(node2);

    auto data = bit_cuda::execute_analysis(nodes, transfer_functions);

    CHECK_MESSAGE(data[0].bitfield == 3, "First node results doesnt match");
    CHECK_MESSAGE(data[1].bitfield == 7, "Second node results doesnt match");
} 

TEST_CASE("worklist cuda x=$ -> y=x") {
    DynamicArray<taint::Node> nodes(2, sizeof(taint::Node));
    std::vector<Transfer> transfer_functions{};

    taint::Node& node1 = nodes.emplace_back();
    node1.first_transfer_index = 0;
    node1.successor_index[0] = 1;
    Transfer& transfer1 = transfer_functions.emplace_back();
    transfer1.var_index = 1;
    transfer1.rhs |= 1;
    
    taint::Node& node2 = nodes.emplace_back();
    node2.first_transfer_index = 1;
    Transfer& transfer2 = transfer_functions.emplace_back();
    transfer2.var_index = 2;
    transfer2.rhs |= 2;
    node2.predecessor_index[0] = 0;

    std::vector<int> taint_sources = {0};
    auto data = cuda_worklist::execute_analysis(nodes, transfer_functions, taint_sources);

    CHECK_MESSAGE(data[0].bitfield == 3, "First node results doesnt match");
    CHECK_MESSAGE(data[1].bitfield == 7, "Second node results doesnt match");
} 


TEST_CASE("worklist cuda multi transforms") {
    DynamicArray<taint::Node> nodes(1, sizeof(taint::Node));
    std::vector<Transfer> transfers;
    taint::Node& node1 = nodes.emplace_back();

    Transfer& transfer1 = transfers.emplace_back();
    transfer1.next_transfer_index = 1;
    node1.first_transfer_index = 0;
    transfer1.var_index = 1;
    transfer1.rhs |= 1;

    Transfer& transfer2 = transfers.emplace_back();
    transfer2.var_index = 2;
    transfer2.rhs |= 1;

    std::vector<int> taint_sources = {0};
    auto data = cuda_worklist::execute_analysis(nodes, transfers, taint_sources);

    CHECK_MESSAGE(data[0].bitfield == 7, "First node results doesnt match");
} 

TEST_CASE("bit cuda multi transforms") {
    DynamicArray<taint::Node> nodes;
    std::vector<Transfer> transfers;
    taint::Node& node1 = nodes.emplace_back();

    Transfer& transfer1 = transfers.emplace_back();
    node1.first_transfer_index = 0;
    transfer1.next_transfer_index = 1;
    transfer1.var_index = 1;
    transfer1.rhs |= 1;

    Transfer& transfer2 = transfers.emplace_back();
    transfer2.var_index = 2;
    transfer2.rhs |= 1;

    auto data = bit_cuda::execute_analysis(nodes, transfers);

    CHECK_MESSAGE(data[0].bitfield == 7, "First node results doesnt match");
} 