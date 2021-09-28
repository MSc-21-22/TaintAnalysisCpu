#include "cfg.h"
#include <ostream>

template <typename LatticeType>
class DigraphPrinter : public CfgVisitor<LatticeType>
{
public:
    std::ostream& os;

    DigraphPrinter(std::ostream& os) : os(os){}

    void visit_initializtion(InitializerNode<LatticeType> &node) override
    {
        os << (unsigned long long int)&node << "[label = \"" << node.type << " "
           << node.id << " = "
           << node.expression->dotPrint() << "\"]\n";
        for (auto &succ : node.successors)
        {
            os << (unsigned long long int)&node << "->" << (unsigned long long int)succ.get() << "\n";
        }
    }
    void visit_assignment(AssignmentNode<LatticeType> &node) override
    {
        os << (unsigned long long int)&node << "[label = \"" << node.id << " = "
           << node.expression->dotPrint() << "\"]\n";
        for (auto &succ : node.successors)
        {
            os << (unsigned long long int)&node << "->" << (unsigned long long int)succ.get() << "\n";
        }
    }
    void visit_functioncall(FunctionCall<LatticeType> &node) override
    {
        os << (unsigned long long int)&node << "[label = \"" << node.functionId << node.arguments << "\n]";
        for (auto &succ : node.successors)
        {
            os << (unsigned long long int)&node << "->" << (unsigned long long int)succ.get() << "\n";
        }
    }
    void visit_functiondef(FunctionDefinition<LatticeType> &node) override
    {
        os << (unsigned long long int)&node << "[label = \"" << node.returnType << " " << node.functionId << "(" << node.formalParameters << ")"
           << "\"]\n";
        for (auto &succ : node.successors)
        {
            os << (unsigned long long int)&node << "->" << (unsigned long long int)succ.get() << "\n";
        }
    }
    void visit_return(ReturnNode<LatticeType> &node) override
    {
        os << (unsigned long long int)&node << "[label = \"" << "return " << node.expression->dotPrint() << "\"]\n";
        for (auto &succ : node.successors)
        {
            os << (unsigned long long int)&node << "->" << (unsigned long long int)succ.get() << "\n";
        }
    }
};


template<typename LatticeType>
void print_digraph(std::vector<std::shared_ptr<Node<LatticeType>>>& nodes, std::ostream& stream){
    DigraphPrinter<LatticeType> printer(stream);

    for(std::shared_ptr<Node<LatticeType>>& node : nodes){
        node->accept(printer);
    }
}