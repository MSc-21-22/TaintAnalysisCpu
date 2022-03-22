// #include "../cuda_data.h"
// #include "../bit_cuda/analysis.h"
// #include "../cuda_worklist/analysis.h"
// #include "analysis.h"
// #include <cfg/cfg.h>
// #include <cfg/transformations/var_visitor.h>
// #include <cfg/transformations/taint_locator.h>

// template<typename NodeType>
// class CudaTransformer : public CfgVisitor
// {
// TaintSourceLocator taint_locator;
// public:
//     std::vector<NodeType> nodes{};
//     std::vector<Transfer> transfer_functions{};
//     std::map<Node*, int> node_to_index{};
//     std::map<std::string, int> variables{};
//     std::set<int> taint_sources{};

//     CudaTransformer(std::set<std::string> progVariables){
//         int i = 0;
//         variables[TAINT_VAR] = i++;
//         variables[RETURN_VAR] = i++;

//         std::set<std::string>::iterator it;
//         for (it=progVariables.begin(); it!=progVariables.end(); it++){
//             if(*it != TAINT_VAR && *it != RETURN_VAR){
//                 variables[*it] = i++;
//             }
//         }

//     }

//     void visit_assignment(AssignmentNode& node) {
//         int id = nodes.size();
//         node_to_index[&node] = id;
//         NodeType& node_struct = nodes.emplace_back();

//         node_struct.first_transfer_index = add_transfer_function(node.id, node.expression);
//         add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
//         node_struct.join_mask ^= 1 << variables[node.id];
//     }

//     void visit_return(ReturnNode& node) {
//         int id = nodes.size();
//         node_to_index[&node] = id;
//         NodeType& node_struct = nodes.emplace_back();

//         node_struct.first_transfer_index = add_transfer_function(RETURN_VAR, node.expression);
//         add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
//         node_struct.join_mask = 0;
//     }

//     void visit_emptyReturn(EmptyReturnNode& node) {
//         node_to_index[&node] = nodes.size();
//         NodeType& node_struct = nodes.emplace_back();
//         node_struct.join_mask = 0;
//     }

//     void visit_functionEntry(FunctionEntryNode& node) { 
//         int id = nodes.size();
//         node_to_index[&node] = id;
//         NodeType& node_struct = nodes.emplace_back();

//         node_struct.join_mask = 0;

//         if(node.arguments.size() >= 1){
//             node_struct.first_transfer_index = add_transfer_function(node.formal_parameters[0], node.arguments[0]);
//             add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
//             Transfer& last = transfer_functions[node_struct.first_transfer_index];
            
//             for (int i = 1; i < node.arguments.size(); i++)
//             {
//                 last.next_transfer_index = add_transfer_function(node.formal_parameters[i], node.arguments[i]);
//                 add_taint_source(id, transfer_functions[last.next_transfer_index]);
//                 last = transfer_functions[last.next_transfer_index];
//             }
//         }
//     }

//     void visit_assignReturn(AssignReturnNode& node) { 
//         int id = nodes.size();
//         node_to_index[&node] = id;
//         NodeType& node_struct = nodes.emplace_back();

//         node_struct.first_transfer_index = add_transfer_function(node.id, {RETURN_VAR});
//         add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
//         node_struct.join_mask ^= 1 << variables[node.id];
//         node_struct.join_mask ^= 1 << variables[RETURN_VAR];
//     }

//     void visit_arrayAssignment(ArrayAssignmentNode& node) { 
//         int id = nodes.size();
//         node_to_index[&node] = id;
//         NodeType& node_struct = nodes.emplace_back();

//         node_struct.first_transfer_index = add_transfer_function(node.id, node.expression);
//         add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
//         node_struct.join_mask ^= 1 << variables[node.id];
//     }
    
//     void visit_arrayinit(ArrayInitializerNode& node) { 
//         int id = nodes.size();
//         node_to_index[&node] = id;
//         NodeType& node_struct = nodes.emplace_back();

//         node_struct.join_mask ^= 1 << variables[node.id];

//         // Get vars from all array element expressions 
//         std::set<std::string> expr_vars;
//         for(auto& element : node.arrayContent){
//             auto vars = element->get_variables();
//             std::set_union(expr_vars.begin(), expr_vars.end(),
//                            vars.begin(), vars.end(),
//                            std::inserter(expr_vars, expr_vars.begin()));
//         }

//         node_struct.first_transfer_index = add_transfer_function(node.id, expr_vars);
//         add_taint_source(id, transfer_functions[node_struct.first_transfer_index]);
//     }

//     void visit_propagation(PropagationNode& node) { 
//         node_to_index[&node] = nodes.size();
//         NodeType& node_struct = nodes.emplace_back();
//     }

// private:
//     int add_transfer_function(std::string x, std::set<std::string>& vars){
//         int index = transfer_functions.size();
//         Transfer& current_transfer = transfer_functions.emplace_back();
//         current_transfer.x = variables[x];
//         fill_with_variable_indices(current_transfer.rhs, vars);
//         return index;
//     }

//     int add_transfer_function(std::string x, std::set<std::string>&& vars){
//         return add_transfer_function(x, vars);
//     }

//     int add_transfer_function(std::string x, std::shared_ptr<Expression>& expression){
//         auto vars = expression->get_variables();
//         return add_transfer_function(x, vars);
//     }

//     void fill_with_variable_indices(int* arr, std::set<std::string>& vars){
//         int i = 0;
//         for(std::string var : vars){
//             if (variables.count(var)){
//                 arr[i++] = variables[var];
//             }
//         } 
//     }

//     void add_taint_source(int nodeIndex, Transfer& transfer){
//         int size = sizeof(transfer.rhs)/sizeof(transfer.rhs[0]);
//         for (int i = 0; i < size; i++){
//             if(transfer.rhs[i] == variables[TAINT_VAR]){
//                 taint_sources.insert(nodeIndex);
//                 break;
//             }
//         }
//     }
// };