#include <cfg.h>
#include <memory>
#include <vector>
#include <var_visitor.h>

#include "transforms_matrix.h"
#include "GpuBoolMatrix.h"
#include "analysis.h"

GpuBoolMatrix run_analysis(const BoolMatrix& initial, const std::vector<BoolMatrix>& transfer_functions, const BoolMatrix& successor){
    GpuBoolMatrix state(initial);
    GpuBoolMatrix succ(successor);
    std::vector<GpuBoolMatrix> expanders;
    std::vector<GpuBoolMatrix> slicers;
    std::vector<GpuBoolMatrix> transfers;

    int i = 0;
    for(auto& transfer : transfer_functions){
        

        transfers.emplace_back(transfer);

        BoolMatrix matrix_slicer(transfer_functions.size(), 1);
        matrix_slicer.add_safe(i, 0);

        slicers.emplace_back(matrix_slicer);

        BoolMatrix matrix_expand(1, transfer_functions.size());
        matrix_expand.add_safe(0, i);

        expanders.emplace_back(matrix_expand);

        ++i;
    }

    GpuBoolMatrix next_state(state.rowCount, state.columnCount);
    GpuBoolMatrix slice(state.rowCount, 1);
    GpuBoolMatrix expanded(state.rowCount, state.columnCount);

    uint32_t old_count = state.get_element_count();
    while(true){
        next_state = state * succ;

        for(size_t i = 0; i < transfers.size(); ++i){
            std::cout << i << '\n';
            slice = next_state * slicers[i];
            expanded = slice * expanders[i];
            expanded = transfers[i] * expanded;
            
            GpuBoolMatrix state_copy(state);
            state = expanded + state_copy;
        }

        uint32_t new_count = state.get_element_count();
        if(new_count == old_count){
            break;
        }else{
            old_count = new_count;
        }
    }
    
    return state;
}

void analyse(std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes){
    std::set<std::string> variables = get_variables(nodes);

    // Create transfer matrices
    BoolMatrixTransforms<std::set<std::string>> matrixTransformer(variables);
    for(auto& node : nodes){
        (*node).accept(matrixTransformer);
    }
    
    // Create successor matrix
    auto successor_matrix = get_successor_matrix<std::set<std::string>>(nodes);
    
    BoolMatrix init_state = initial_matrix(matrixTransformer.variables.size(), nodes.size());
    auto result_state = run_analysis(init_state, matrixTransformer.matrices, successor_matrix);
    // Set the tainted state on nodes
    std::cout << result_state.retrieve_from_gpu();
    
    //set_node_states(result_state, nodes, matrixTransformer.variables);
}

void cubool_analyse(std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes){
    create_cubool();
    analyse(nodes);
    destroy_cubool();
}