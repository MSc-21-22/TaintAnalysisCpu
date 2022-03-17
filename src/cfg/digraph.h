#pragma once

#include <cfg/cfg.h>
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

    int i = 0;
    for (StatefulNode<LatticeType> &state_node : nodes)
    {

        stream << (unsigned long long int)state_node.node.get() << "[label = \"x" << i++ << ": ";
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
void print_digraph_subgraph(std::vector<StatefulNode<LatticeType>> &nodes, std::ostream &stream, PrintLambda lattice_printer, std::string analyzeFunction)
{
    DigraphPrinter printer(stream);
    std::vector<StatefulNode<LatticeType>> nodesToPrint = {};

    for(StatefulNode<LatticeType>& node : nodes) {
        FunctionEntryNode* entry_node = dynamic_cast<FunctionEntryNode*>(node.node.get());
        if(entry_node != nullptr)
        {
            if(entry_node->function_id == analyzeFunction)
            {
                for (auto& succ : node.get_successors()){
                    nodesToPrint.push_back(node);
                    std::set<unsigned long long int> checked = {};
                    findFunctionEntries(succ, nodesToPrint, checked);
                } 

                for (auto& node : nodesToPrint)
                {
                    for (auto& succ : node.get_successors())
                    {
                        stream << (unsigned long long int)node.node.get() << "[label = \"";
                        node.accept(printer);
                        lattice_printer(node.get_state(), stream);
                        stream << "\"]\n";
                        std::string returnpath = "";
                        printer.visitedNodes.insert((unsigned long long int)node.node.get());
                        stream << connectNodes(node.node, succ.node);
                        stream << "subgraph cluster_" << (unsigned long long int)node.node.get() << "{\n";
                        print_digraph_subgraph_content(succ, stream, printer, returnpath, lattice_printer);
                        stream << "}\n";
                        stream << returnpath;     
                    }
                } 
            }
        }
    }

}

template <typename LatticeType, typename PrintLambda>
void print_digraph_subgraph_content(StatefulNode<LatticeType> &node, std::ostream &stream, DigraphPrinter &printer, std::string &returnpath, PrintLambda lattice_printer){
    stream << (unsigned long long int)node.node.get() << "[label = \"";
    node.accept(printer);
    lattice_printer(node.get_state(), stream);
    stream << "\"]\n";
    printer.visitedNodes.insert((unsigned long long int)node.node.get());
    if (dynamic_cast<ReturnNode*>(node.node.get()) || dynamic_cast<EmptyReturnNode*>(node.node.get()))
    {
        for (auto& succ : node.get_successors())
        {
            returnpath.append(connectNodes(node.node, succ.node));
            PropagationNode* prop_node = dynamic_cast<PropagationNode*>(succ.node.get());
            if(prop_node)
            {
                if(prop_node->syntax == "Exit"){
                    returnpath.append(std::to_string((unsigned long long int)succ.node.get())+"[label = \" Exit\"]\n");
                    for (auto &exitsucc : succ.get_successors())
                    {
                        returnpath.append(connectNodes(succ.node, exitsucc.node));
                    }
                }
                
            }
        }
    }
    else
    {
        for (auto& succ : node.get_successors())
        {
            if (dynamic_cast<FunctionEntryNode*>(succ.node.get()))
            {
                returnpath.append(connectNodes(node.node, succ.node));
            }
            else
            {
                stream << connectNodes(node.node, succ.node);

                if(printer.visitedNodes.find((unsigned long long int)succ.node.get()) == printer.visitedNodes.end())
                {
                    print_digraph_subgraph_content(succ, stream, printer, returnpath, lattice_printer);
                }
            }
        }
    }
}

template<typename LatticeType>
void findFunctionEntries(StatefulNode<LatticeType> &node, std::vector<StatefulNode<LatticeType>> &nodesToPrint, std::set<unsigned long long int> &checked)
{
    for (auto& succ : node.get_successors())
    {
         if(checked.find((unsigned long long int)succ.node.get()) == checked.end())
         {
            if (dynamic_cast<FunctionEntryNode*>(succ.node.get()))
            {
                nodesToPrint.push_back(succ);
            }
            checked.insert((unsigned long long int)succ.node.get());
            findFunctionEntries(succ, nodesToPrint, checked);
        }
    }
}

std::string connectNodes(std::shared_ptr<Node> const &pred, std::shared_ptr<Node> const &succ);