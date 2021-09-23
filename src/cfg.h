#include <unordered_set>
#include <memory>
#include <string>
#include <vector>

template<typename LatticeType>
class Node {
public:
    std::unordered_set<std::shared_ptr<Node>> predecessors;
    std::unordered_set<std::shared_ptr<Node>> successors;
    std::shared_ptr<LatticeType> state;
};

template<typename LatticeType>
class InitializerNode : public Node<LatticeType> {
public:
    std::string type; // Consider switching to enum
    std::string id;
    std::string expression; // Type should probably be changed
};

template<typename LatticeType>
class AssignmentNode : public Node<LatticeType> {
public:
    std::string id;
    std::string expression;
};

template<typename LatticeType>
class FunctionCall : public Node<LatticeType> {
public:
    std::string functionId;
    std::vector<std::string> arguments;
};

template<typename LatticeType>
class FunctionDefinition : public Node<LatticeType> {
public:
    std::string functionId;
    std::vector<std::string> formalParameters;
    std::string returnType;
};

template<typename LatticeType>
class ReturnNode : public Node<LatticeType> {
public:
    std::string expression;
};