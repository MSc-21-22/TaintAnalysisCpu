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
};

template <typename LatticeType>
void print_digraph(std::vector<std::shared_ptr<Node<LatticeType>>> &nodes, std::ostream &stream)
{
    DigraphPrinter<LatticeType> printer(stream);

    for (std::shared_ptr<Node<LatticeType>> &node : nodes)
    {
        stream << (unsigned long long int)&node << "[label = \"";
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