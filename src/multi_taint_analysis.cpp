#include "multi_taint_analysis.h"

SourcedTaintState least_upper_bound(const SourcedTaintState& left, const SourcedTaintState& right){
    SourcedTaintState state;
    for (SourcedTaintState::const_iterator it=left.begin(); it!=left.end(); ++it){
        state[it->first] = it->second;
    }
    for (SourcedTaintState::const_iterator it=right.begin(); it!=right.end(); ++it){
        for(auto& taint_source : it->second){
            state[it->first].insert(taint_source);
        }
    }
    return state;
}

SourcedTaintState join(Node<SourcedTaintState>& node){
    if (node.predecessors.size() == 0)
        return {};

    auto it = node.predecessors.begin();
    auto state = (*it)->state;
    it++;
    while(it != node.predecessors.end())
    {
        state = least_upper_bound((*it)->state, state);
        it++;
    }
    return state;
}

std::set<int> MultiTaintAnalyzer::get_taints(std::shared_ptr<Expression> expression, Node<SourcedTaintState>&node)
{
    std::set<int> sources;
    for (auto& var : expression->get_variables()){
        if(var == "£"){
            if (node_to_source.find((long long int)&node) == node_to_source.end()){
                node_to_source[(long long int)&node] = next_source++;
            }

            sources.insert(node_to_source[(long long int)&node]);
        }else{
            for(auto& source: node.state[var]){
                sources.insert(source);
            }
        }
    }
    return sources;
}

void MultiTaintAnalyzer::visit_propagation(PropagationNode<SourcedTaintState>& node){
    node.state = join(node);
}

void MultiTaintAnalyzer::visit_arrayinit(ArrayInitializerNode<SourcedTaintState>& node){
    node.state = join(node);
    for (auto &expression : node.arrayContent)
    {
        node.state[node.id].merge(get_taints(expression, node));
    }
}

void MultiTaintAnalyzer::visit_assignment(AssignmentNode<SourcedTaintState>& node){
    node.state = join(node);
    node.state[node.id] = get_taints(node.expression, node);
}

void MultiTaintAnalyzer::visit_arrayAssignment(ArrayAssignmentNode<SourcedTaintState>& node){
    node.state = join(node);
    node.state[node.id] = get_taints(node.expression, node);
}

void MultiTaintAnalyzer::visit_return(ReturnNode<SourcedTaintState>& node){
    auto state = join(node);

    node.state["£return"] = get_taints(node.expression, node);
}
void MultiTaintAnalyzer::visit_emptyReturn(EmptyReturnNode<SourcedTaintState>& node){
    node.state["£return"] = {};
}
void MultiTaintAnalyzer::visit_functionEntry(FunctionEntryNode<SourcedTaintState>& node){
    auto state = join(node);
    
    if (node.successors.size() == 0)
        return;

    auto previous_node = node.predecessors.begin();

    for(size_t i = 0; i < node.arguments.size(); ++i){
        auto taint_sources = get_taints(node.arguments[i], **previous_node);
        auto parameter = node.formal_parameters[i];
        node.state[parameter] = taint_sources;
    }
}

void MultiTaintAnalyzer::visit_assignReturn(AssignReturnNode<SourcedTaintState>& node){
    node.state = join(node);
    node.state[node.id] = node.state["£return"];
    node.state["£return"] = {};
}

void print_taint_source(SourcedTaintState& result, std::ostream& stream){
    stream << "\\n{ ";
    for (auto& variable_pair : result){
        if(variable_pair.second.size() == 0)
            continue;

        std::cout << variable_pair.first << ":[";
        for(auto& source : variable_pair.second){
            std::cout << source << ", ";
        }
        std::cout << "]\\n";
    }
    stream << "}";
}