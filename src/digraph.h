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
    void visit_emptyReturn(EmptyReturnNode<LatticeType> &node) override
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

    void visit_functionEntry(FunctionEntryNode<LatticeType> &node) override {
        os << "Entry";
    }

    void visit_functionExit(FunctionExitNode<LatticeType> &node) override {
        os << "Exit";
    }
    
    void visit_assignReturn(AssignReturnNode<LatticeType>& node) override {
        os << node.id << " = £return";
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

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Expression>& arg){
    os << arg->dotPrint();
    return os;
}

template <typename LatticeType, typename PrintLambda>
void print_digraph_subgraph(std::vector<std::shared_ptr<FunctionEntryNode<LatticeType>>> &entryNodes, std::ostream &stream, PrintLambda lattice_printer){
    DigraphPrinter<LatticeType> printer(stream);
    for (auto& entryNode : entryNodes)
    {
        stream << (unsigned long long int)entryNode.get() << "[label = \"";
        entryNode->accept(printer);
        stream << "\"]\n";
        std::string returnpath = "";
        printer.visitedNodes.insert((unsigned long long int)entryNode.get());
        for (auto& succ : entryNode->successors)
        {
            stream << (unsigned long long int)entryNode.get() << "->" << (unsigned long long int)succ.get() << "\n";
            stream << "subgraph cluster_" << (unsigned long long int)entryNode.get() << "{\n";
            print_digraph_subgraph_content(succ, stream, printer, returnpath, lattice_printer);
            stream << "}\n";
            stream << returnpath;
            returnpath = "";
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
    if (dynamic_cast<ReturnNode<LatticeType>*>(node.get()))
    {
        for (auto& succ : node->successors)
        {
            returnpath.append(std::to_string((unsigned long long int)node.get())+"->");
            returnpath.append(std::to_string((unsigned long long int)succ.get())+"\n");
            if(dynamic_cast<FunctionExitNode<LatticeType>*>(succ.get()))
            {
                returnpath.append(std::to_string((unsigned long long int)succ.get())+"[label = \" exit\"]\n");
                for (auto exitsucc : succ->successors)
                {
                    returnpath.append(std::to_string((unsigned long long int)succ.get())+"->");
                    returnpath.append(std::to_string((unsigned long long int)exitsucc.get())+"\n");
                }
                
            }
        }
    }
    else if (dynamic_cast<EmptyReturnNode<LatticeType>*>(node.get()))
    {
       for (auto& succ : node->successors)
        {
            returnpath.append(std::to_string((unsigned long long int)node.get())+"->");
            returnpath.append(std::to_string((unsigned long long int)succ.get())+"\n");
            if(dynamic_cast<FunctionExitNode<LatticeType>*>(succ.get()))
            {
                returnpath.append(std::to_string((unsigned long long int)succ.get())+"[label = \" exit\"]\n");
                for (auto exitsucc : succ->successors)
                {
                    returnpath.append(std::to_string((unsigned long long int)succ.get())+"->");
                    returnpath.append(std::to_string((unsigned long long int)exitsucc.get())+"\n");
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
                returnpath.append(std::to_string((unsigned long long int)node.get())+"->"+std::to_string((unsigned long long int)succ.get())+"\n");
            }
            else
            {
                stream << (unsigned long long int)node.get() << "->" << (unsigned long long int)succ.get() << "\n";
                
                if(printer.visitedNodes.find((unsigned long long int)succ.get()) == printer.visitedNodes.end())
                {
                    print_digraph_subgraph_content(succ, stream, printer, returnpath, lattice_printer);
                }
            }
        }
    }
}