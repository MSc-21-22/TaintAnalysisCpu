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

template <typename LatticeType>
class DigraphPrinter : public CfgVisitor<LatticeType>
{
public:
    std::ostream &os;

    std::set<unsigned long long int> visitedNodes = {};

    DigraphPrinter(std::ostream &os) : os(os) {}

    void visit_initializtion(InitializerNode<LatticeType> &node) override
    {
        os << node.type << " " << node.id << " = " << node.expression->dotPrint();
    }
    void visit_assignment(AssignmentNode<LatticeType> &node) override
    {
        os << node.id << " = " << node.expression->dotPrint();
    }
    void visit_arrayAssignment(ArrayAssignmentNode<LatticeType> &node) override
    {
        os << node.id << " = " << node.expression->dotPrint();
    }
    void visit_functioncall(FunctionCall<LatticeType> &node) override
    {
        os << node.type << " " << node.variableId << " = " << node.functionId << "(" << node.arguments << ")";
    }
    void visit_functiondef(FunctionDefinition<LatticeType> &node) override
    {
        os << node.returnType << " " << node.functionId << "(" << node.formalParameters << ")";
    }
    void visit_return(ReturnNode<LatticeType> &node) override
    {
        os << "return " << node.expression->dotPrint();
    }
    void visit_emptyReturn(EmptyReturnNode<LatticeType> &) override
    {
        os << "return";
    }
    void visit_whileloop(WhileLoop<LatticeType> &node) override
    {
        os << "while(" << node.condition->dotPrint() << ")";
    }

    void visit_if(IfNode<LatticeType> &node) override
    {
        os << "if(" << node.expression->dotPrint() << ")";
    }

    void visit_functionEntry(FunctionEntryNode<LatticeType>&) override {
        os << "Entry\n";
    }

    void visit_functionExit(FunctionExitNode<LatticeType>&) override {
        os << "Exit";
    }
    
    void visit_assignReturn(AssignReturnNode<LatticeType>& node) override {
        os << node.id << " = £return";
    }

    void  visit_arrayinit(ArrayInitializerNode<LatticeType>& node) override {
        os << node.type << " " << node.id << "[" << node.arraySize->dotPrint() << "] = {";
        for (auto &element : node.arrayContent)
        {
            os << element->dotPrint() << ", ";
        }
        os << "}"; 
    }
};

template <typename LatticeType>
void print_digraph(std::vector<std::shared_ptr<Node<LatticeType>>> &nodes, std::ostream &stream)
{
    DigraphPrinter<LatticeType> printer(stream);

    for (std::shared_ptr<Node<LatticeType>> &node : nodes)
    {
        stream << (unsigned long long int)node.get() << "[label = \"";
        node->accept(printer);
        stream << "\"]\n";

        for (auto &succ : node->successors)
        {
            stream << (unsigned long long int)node.get() << "->" << (unsigned long long int)succ.get() << "\n";
        }
    }
}


template <typename LatticeType, typename PrintLambda>
void print_digraph_with_result(std::vector<std::shared_ptr<Node<LatticeType>>> &nodes, std::ostream &stream, PrintLambda lattice_printer)
{
    DigraphPrinter<LatticeType> printer(stream);

    for (std::shared_ptr<Node<LatticeType>> &node : nodes)
    {

        stream << (unsigned long long int)node.get() << "[label = \"";
        node->accept(printer);
        lattice_printer(node->state, stream);
        stream << "\"]\n";

        for (auto &succ : node->successors)
        {
            stream << (unsigned long long int)node.get() << "->" << (unsigned long long int)succ.get() << "\n";
        }
    }
}


std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Expression>& arg);

template <typename LatticeType, typename PrintLambda>
void print_digraph_subgraph(std::vector<std::shared_ptr<FunctionEntryNode<LatticeType>>> &entryNodes, std::ostream &stream, PrintLambda lattice_printer, std::string analyzeFunction)
{
    DigraphPrinter<LatticeType> printer(stream);
    std::vector<std::shared_ptr<Node<LatticeType>>> nodesToPrint = {};

    for (auto& entryNode : entryNodes)
    {
        for (auto& succ : entryNode->successors)
        {
            if(auto funcDef = dynamic_cast<FunctionDefinition<LatticeType>*>(succ.get()))
            {
                if(funcDef->functionId == analyzeFunction)
                {
                    nodesToPrint.push_back(entryNode);
                    std::set<unsigned long long int> checked = {};
                    findFunctionEntries(succ, nodesToPrint, checked);
                }
            }
        }   
    }
    for (auto& node : nodesToPrint)
    {
        for (auto& succ : node->successors)
        {
            stream << (unsigned long long int)node.get() << "[label = \"";
            node->accept(printer);
            lattice_printer(node->state, stream);
            stream << "\"]\n";
            std::string returnpath = "";
            printer.visitedNodes.insert((unsigned long long int)node.get());
            stream << connectNodes(node, succ);
            stream << "subgraph cluster_" << (unsigned long long int)node.get() << "{\n";
            print_digraph_subgraph_content(succ, stream, printer, returnpath, lattice_printer);
            stream << "}\n";
            stream << returnpath;     
        }
    } 
}

template <typename LatticeType, typename PrintLambda>
void print_digraph_subgraph_content(std::shared_ptr<Node<LatticeType>> const &node, std::ostream &stream, DigraphPrinter<LatticeType> &printer, std::string &returnpath, PrintLambda lattice_printer){
    stream << (unsigned long long int)node.get() << "[label = \"";
    node->accept(printer);
    lattice_printer(node->state, stream);
    stream << "\"]\n";
    printer.visitedNodes.insert((unsigned long long int)node.get());
    if (dynamic_cast<ReturnNode<LatticeType>*>(node.get()) || dynamic_cast<EmptyReturnNode<LatticeType>*>(node.get()))
    {
        for (auto& succ : node->successors)
        {
            returnpath.append(connectNodes(node, succ));
            if(dynamic_cast<FunctionExitNode<LatticeType>*>(succ.get()))
            {
                returnpath.append(std::to_string((unsigned long long int)succ.get())+"[label = \" Exit\"]\n");
                for (auto exitsucc : succ->successors)
                {
                    returnpath.append(connectNodes(succ, exitsucc));
                }
                
            }
        }
    }
    else
    {
        for (auto& succ : node->successors)
        {
            if (dynamic_cast<FunctionEntryNode<LatticeType>*>(succ.get()))
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

template<typename LatticeType>
void findFunctionEntries(std::shared_ptr<Node<LatticeType>> const &node, std::vector<std::shared_ptr<Node<LatticeType>>> &nodesToPrint, std::set<unsigned long long int> &checked)
{
    for (auto& succ : node->successors)
    {
         if(checked.find((unsigned long long int)succ.get()) == checked.end())
         {
            if (dynamic_cast<FunctionEntryNode<LatticeType>*>(succ.get()))
            {
                nodesToPrint.push_back(succ);
            }
            checked.insert((unsigned long long int)succ.get());
            findFunctionEntries(succ, nodesToPrint, checked);
        }
    }
}

template<typename LatticeType>
std::string connectNodes(std::shared_ptr<Node<LatticeType>> const &pred, std::shared_ptr<Node<LatticeType>> const &succ)
{
    return std::to_string((unsigned long long int)pred.get())+"->"+std::to_string((unsigned long long int)succ.get())+"\n";
}