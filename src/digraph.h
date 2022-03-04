#pragma once

#include "cfg.h"
#include <ostream>

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec){
    auto it = vec.begin();
    while(it != vec.end()){
        stream << *it;

        it++;
        if (it != vec.end()){
            stream << ", ";
        }
    }

    return stream;
}

class DigraphPrinter : public CfgVisitor
{
public:
    std::ostream &os;

    std::set<unsigned long long int> visitedNodes = {};

    DigraphPrinter(std::ostream &os) : os(os) {}

    void visit_propagation(PropagationNode &node) override;
    void visit_assignment(AssignmentNode &node) override;
    void visit_arrayAssignment(ArrayAssignmentNode &node) override;
    void visit_return(ReturnNode &node) override;
    void visit_emptyReturn(EmptyReturnNode &) override;
    void visit_functionEntry(FunctionEntryNode&) override;
    void visit_assignReturn(AssignReturnNode& node) override;
    void visit_arrayinit(ArrayInitializerNode& node) override;
};

void print_digraph(std::vector<std::shared_ptr<Node>> &nodes, std::ostream &stream);


template <typename LatticeType, typename PrintLambda>
void print_digraph_with_result(std::vector<StatefulNode<LatticeType>> &nodes, std::ostream &stream, PrintLambda lattice_printer)
{
    DigraphPrinter printer(stream);

    stream << "Hello" << nodes.size();

    for (StatefulNode<LatticeType> &state_node : nodes)
    {

        stream << (unsigned long long int)state_node.node.get() << "[label = \"";
        state_node.node->accept(printer);
        lattice_printer(state_node.get_state(), stream);
        stream << "\"]\n";

        for (auto &succ : state_node.node->successors)
        {
            stream << (unsigned long long int)state_node.node.get() << "->" << (unsigned long long int)succ.get() << "\n";
        }
    }
}


std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Expression>& arg);

template <typename LatticeType, typename PrintLambda>
void print_digraph_subgraph(std::vector<StatefulNode<LatticeType>> &entryNodes, std::ostream &stream, PrintLambda lattice_printer, std::string analyzeFunction)
{
    DigraphPrinter printer(stream);
    std::vector<std::shared_ptr<Node>> nodesToPrint = {};

    for (StatefulNode<LatticeType>& entryNode : entryNodes)
    {
        for (auto& succ : entryNode.node->successors){
            if(entryNode->function_id == analyzeFunction)
            {
                nodesToPrint.push_back(entryNode.node);
                std::set<unsigned long long int> checked = {};
                findFunctionEntries(succ, nodesToPrint, checked);
            }
        }  
    }
    for (auto& node : nodesToPrint)
    {
        for (auto& succ : node->successors)
        {
            stream << (unsigned long long int)node.get() << "[label = \"";
            node->accept(printer);
            lattice_printer(entryNodes[0].states[&node], stream);
            stream << "\"]\n";
            std::string returnpath = "";
            printer.visitedNodes.insert((unsigned long long int)node.get());
            stream << connectNodes(node, succ);
            stream << "subgraph cluster_" << (unsigned long long int)node.get() << "{\n";
            print_digraph_subgraph_content(succ, stream, printer, returnpath, [states=entryNodes[0].states, lattice_printer](Node* node){lattice_printer(states[node]);});
            stream << "}\n";
            stream << returnpath;     
        }
    } 
}

template <typename PrintLambda>
void print_digraph_subgraph_content(std::shared_ptr<Node> const &node, std::ostream &stream, DigraphPrinter &printer, std::string &returnpath, PrintLambda lattice_printer){
    stream << (unsigned long long int)node.get() << "[label = \"";
    node->accept(printer);
    lattice_printer(node.get());
    stream << "\"]\n";
    printer.visitedNodes.insert((unsigned long long int)node.get());
    if (dynamic_cast<ReturnNode*>(node.get()) || dynamic_cast<EmptyReturnNode*>(node.get()))
    {
        for (auto& succ : node->successors)
        {
            returnpath.append(connectNodes(node, succ));
            PropagationNode* prop_node = dynamic_cast<PropagationNode*>(succ.get());
            if(prop_node)
            {
                if(prop_node->syntax == "Exit"){
                    returnpath.append(std::to_string((unsigned long long int)succ.get())+"[label = \" Exit\"]\n");
                    for (auto exitsucc : succ->successors)
                    {
                        returnpath.append(connectNodes(succ, exitsucc));
                    }
                }
                
            }
        }
    }
    else
    {
        for (auto& succ : node->successors)
        {
            if (dynamic_cast<FunctionEntryNode*>(succ.get()))
            {
                returnpath.append(connectNodes(node, succ));
            }
            else
            {
                stream << connectNodes(node, succ);

                if(printer.visitedNodes.find((unsigned long long int)succ.get()) == printer.visitedNodes.end())
                {
                    print_digraph_subgraph_content(succ, stream, printer, returnpath, lattice_printer);
                }
            }
        }
    }
}

void findFunctionEntries(std::shared_ptr<Node> const &node, std::vector<std::shared_ptr<Node>> &nodesToPrint, std::set<unsigned long long int> &checked);

std::string connectNodes(std::shared_ptr<Node> const &pred, std::shared_ptr<Node> const &succ);