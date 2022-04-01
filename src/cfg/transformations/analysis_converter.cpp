#include "analysis_converter.h"

using namespace cpu_analysis;

TransferCreator::TransferCreator(){
    var_map[TAINT_VAR] = 0;
}

int TransferCreator::get_var_index(const std::string& var){
    if(var_map.count(var) == 0){
        var_map[var] = next_var_index;
        return next_var_index++;
    }else{
        return var_map[var];
    }
}

void TransferCreator::visit_assignment(AssignmentNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = get_var_index(node.id);
    transfer.join_mask.flip_bit(transfer.var_index);
    for(auto& variable : node.expression->get_variables()){
        auto index = get_var_index(variable);
        transfer.transfer_mask.set_bit(index);
    }
}
void TransferCreator::visit_return(ReturnNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = get_var_index(RETURN_VAR);
    transfer.join_mask = 0;
    for(auto& variable : node.expression->get_variables()){
        transfer.transfer_mask.set_bit(get_var_index(variable));
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

        transfer.var_index = get_var_index(node.formal_parameters[i]);
        for(auto& variable : node.arguments[i]->get_variables()){
            transfer.transfer_mask.set_bit(get_var_index(variable));
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
    transfer.var_index = get_var_index(node.id);
    transfer.join_mask.flip_bit(transfer.var_index);
    transfer.join_mask.flip_bit(get_var_index(RETURN_VAR));
    transfer.transfer_mask.set_bit(get_var_index(RETURN_VAR));
}
void TransferCreator::visit_arrayAssignment(ArrayAssignmentNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = get_var_index(node.id);
    transfer.join_mask.flip_bit(transfer.var_index);
    for(auto& variable : node.expression->get_variables()){
        transfer.transfer_mask.set_bit(get_var_index(variable));
    }
}
void TransferCreator::visit_arrayinit(ArrayInitializerNode& node) {
    Transfer& transfer = transfers.emplace_back();
    transfer.var_index = get_var_index(RETURN_VAR);
    transfer.join_mask.flip_bit(transfer.var_index);
    for(auto& expr : node.arrayContent) {
        for(auto& variable : expr->get_variables()){
            transfer.transfer_mask.set_bit(get_var_index(variable));
        }
    }
}
void TransferCreator::visit_propagation(PropagationNode& node) {
    transfers.emplace_back();
}

#include <iostream>

TransferCreator get_analysis_information(std::vector<std::shared_ptr<Node>>& nodes) {
    TransferCreator transforCreator;
    for(int i = 0; i < nodes.size(); ++i){
        transforCreator.node_to_index.emplace_back(transforCreator.transfers.size());
        nodes[i]->accept(transforCreator);
    }

    return transforCreator;
}