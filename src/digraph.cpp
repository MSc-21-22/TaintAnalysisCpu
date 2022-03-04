#include "digraph.h"

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Expression>& arg){
    os << arg->dotPrint();
    return os;
}

void DigraphPrinter::visit_propagation(PropagationNode &node)
{
    os << node.syntax;
}
void DigraphPrinter::visit_assignment(AssignmentNode &node)
{
    os << node.id << " = " << node.expression->dotPrint();
}

void DigraphPrinter::visit_arrayAssignment(ArrayAssignmentNode &node)
{
    os << node.id << " = " << node.expression->dotPrint();
}

void DigraphPrinter::visit_return(ReturnNode &node)
{
    os << "return " << node.expression->dotPrint();
}
void DigraphPrinter::visit_emptyReturn(EmptyReturnNode &)
{
    os << "return";
}

void DigraphPrinter::visit_functionEntry(FunctionEntryNode&) {
    os << "Entry\n";
}

void DigraphPrinter::visit_assignReturn(AssignReturnNode& node) {
    os << node.id << " = " << RETURN_VAR;
}

void DigraphPrinter::visit_arrayinit(ArrayInitializerNode& node) {
    os << node.type << " " << node.id << "[" << node.arraySize << "] = {";
    for (auto &element : node.arrayContent)
    {
        os << element->dotPrint() << ", ";
    }
    os << "}"; 
}

void print_digraph(std::vector<std::shared_ptr<Node>> &nodes, std::ostream &stream)
{
    DigraphPrinter printer(stream);

    for (std::shared_ptr<Node> &node : nodes)
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

void findFunctionEntries(std::shared_ptr<Node> const &node, std::vector<std::shared_ptr<Node>> &nodesToPrint, std::set<unsigned long long int> &checked)
{
    for (auto& succ : node->successors)
    {
         if(checked.find((unsigned long long int)succ.get()) == checked.end())
         {
            if (dynamic_cast<FunctionEntryNode*>(succ.get()))
            {
                nodesToPrint.push_back(succ);
            }
            checked.insert((unsigned long long int)succ.get());
            findFunctionEntries(succ, nodesToPrint, checked);
        }
    }
}

std::string connectNodes(std::shared_ptr<Node> const &pred, std::shared_ptr<Node> const &succ)
{
    return std::to_string((unsigned long long int)pred.get())+"->"+std::to_string((unsigned long long int)succ.get())+"\n";
}