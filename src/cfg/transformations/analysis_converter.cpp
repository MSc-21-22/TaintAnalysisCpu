#include "analysis_converter.h"
#include <assert.h>

using namespace cpu_analysis;

void TransferCreator::visit_assignment(AssignmentNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = node.var_index;
    transfer.join_mask.flip_bit(transfer.var_index);
    for(auto& index : node.expression->get_indicies()){
        transfer.transfer_mask.set_bit(index);
    }
}
void TransferCreator::visit_return(ReturnNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = RETURN_VAR_INDEX;
    transfer.join_mask = 0;
    for(auto& index : node.expression->get_indicies()){
        transfer.transfer_mask.set_bit(index);
    }
}
void TransferCreator::visit_emptyReturn(EmptyReturnNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.join_mask = 0;
}
void TransferCreator::visit_functionEntry(FunctionEntryNode& node) {
    for(int i = 0; i < node.arguments.size(); ++i){
        Transfer& transfer = transfers.emplace_back();
        transfer.join_mask = 0;

        transfer.var_index = node.formal_parameter_indexes[i];
        for(auto& index : node.arguments[i]->get_indicies()){
            transfer.transfer_mask.set_bit(index);
        }
        transfer.uses_next = true;
    }

    if(node.arguments.size() == 0){
        Transfer& transfer = transfers.emplace_back();
        transfer.join_mask = 0;
    }

    transfers.back().uses_next = false;
}
void TransferCreator::visit_assignReturn(AssignReturnNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = node.var_index;
    transfer.join_mask.flip_bit(transfer.var_index);
    transfer.join_mask.flip_bit(RETURN_VAR_INDEX);
    transfer.transfer_mask.set_bit(RETURN_VAR_INDEX);
}
void TransferCreator::visit_arrayAssignment(ArrayAssignmentNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = node.var_index;
    transfer.join_mask.flip_bit(transfer.var_index);
    for(auto& index : node.expression->get_indicies()){
        transfer.transfer_mask.set_bit(index);
    }
}
void TransferCreator::visit_arrayinit(ArrayInitializerNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = RETURN_VAR_INDEX;
    transfer.join_mask.flip_bit(transfer.var_index);
    for(auto& expr : node.arrayContent) {
        for(auto& index : expr->get_indicies()){
            transfer.transfer_mask.set_bit(index);
        }
    }
}
void TransferCreator::visit_propagation(PropagationNode& node) {
    transfers.emplace_back();
}

TransferCreator get_analysis_information(std::vector<std::shared_ptr<Node>>& nodes) {
    TransferCreator transforCreator;
    for(int i = 0; i < nodes.size(); ++i){
        transforCreator.node_to_index.emplace_back(transforCreator.transfers.size());
        nodes[i]->accept(transforCreator);
    }

    return transforCreator;
}