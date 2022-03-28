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

SourcedTaintState join(Node& node, std::map<Node*, SourcedTaintState>& states){
    if (node.predecessors.size() == 0)
        return {};

    SourcedTaintState state = states[&node];
    auto old_taint_constant = state[TAINT_VAR];
    auto it = node.predecessors.begin();
    while(it != node.predecessors.end())
    {
        state = least_upper_bound(states[it->get()], state);
        it++;
    }

    //Dont propagate taint sources
    state[TAINT_VAR] = old_taint_constant;

    return state;
}

std::set<int> MultiTaintAnalyzer::get_taints(std::shared_ptr<Expression> expression, const Node& node, SourcedTaintState& state)
{
    std::set<int> sources;
    for (auto& var : expression->get_variables()){
        if(var == TAINT_VAR){
            if (node_to_source.find((long long int)&node) == node_to_source.end()){
                node_to_source[(long long int)&node] = next_source++;
            }

            sources.insert(node_to_source[(long long int)&node]);
        }else{
            for(auto& source: state[var]){
                sources.insert(source);
            }
        }
    }
    return sources;
}

void MultiTaintAnalyzer::visit_propagation(PropagationNode& node, std::map<Node*, SourcedTaintState>& states){
    SourcedTaintState& node_state = states[&node];
    node_state = join(node, states);
}

void MultiTaintAnalyzer::visit_arrayinit(ArrayInitializerNode& node, std::map<Node*, SourcedTaintState>& states){
    SourcedTaintState& node_state = states[&node];
    node_state = join(node, states);
    for (auto &expression : node.arrayContent)
    {
        std::set<int> taints = get_taints(expression, node, states[&node]);
        std::set_union(node_state[node.id].begin(), node_state[node.id].end(), taints.begin(), taints.end(), std::inserter(node_state[node.id], node_state[node.id].begin()));
    }
}

void MultiTaintAnalyzer::visit_assignment(AssignmentNode& node, std::map<Node*, SourcedTaintState>& states){
    states[&node] = join(node, states);
    states[&node][node.id] = get_taints(node.expression, node, states[&node]);
}

void MultiTaintAnalyzer::visit_arrayAssignment(ArrayAssignmentNode& node, std::map<Node*, SourcedTaintState>& states){
    states[&node] = join(node, states);
    states[&node][node.id] = get_taints(node.expression, node, states[&node]);
}

void MultiTaintAnalyzer::visit_return(ReturnNode& node, std::map<Node*, SourcedTaintState>& states){
    auto state = join(node, states);
    states[&node][RETURN_VAR] = get_taints(node.expression, node, state);
}
void MultiTaintAnalyzer::visit_emptyReturn(EmptyReturnNode& node, std::map<Node*, SourcedTaintState>& states){
    states[&node][RETURN_VAR] = {};
}
void MultiTaintAnalyzer::visit_functionEntry(FunctionEntryNode& node, std::map<Node*, SourcedTaintState>& states){
    SourcedTaintState& node_state = states[&node];
    auto state = join(node, states);
    
    if (node.successors.size() == 0)
        return;

    auto previous_node = node.predecessors.begin();

    for(size_t i = 0; i < node.arguments.size(); ++i){
        auto taint_sources = get_taints(node.arguments[i], **previous_node, states[previous_node->get()]);
        auto parameter = node.formal_parameters[i];
        node_state[parameter] = taint_sources;
    }
}

void MultiTaintAnalyzer::visit_assignReturn(AssignReturnNode& node, std::map<Node*, SourcedTaintState>& states){
    states[&node] = join(node, states);
    states[&node][node.id] = states[&node][RETURN_VAR];
    states[&node][RETURN_VAR] = {};
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