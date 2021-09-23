#include <unordered_set>
#include <memory>
#include <string>
#include <vector>

class Node {
public:
    std::unordered_set<std::shared_ptr<Node>> predecessors;
};

class InitializerNode : public Node {
public:
    std::string type; // Consider switching to enum
    std::string id;
    std::string expression; // Type should probably be changed
};

class AssignmentNode : public Node {
public:
    std::string id;
    std::string expression;
};

class FunctionCall : public Node {
public:
    std::string functionId;
    std::vector<std::string> arguments;
};

class FunctionDefinition : public Node {
public:
    std::string functionId;
    std::vector<std::string> formalParameters;
    std::string returnType;
};

class ReturnNode : public Node {
public:
    std::string expression;
};