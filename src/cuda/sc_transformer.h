#include "antlr4-runtime/scBaseVisitor.h"
#include <memory>
#include "antlr4-runtime/scParser.h"
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <dynamic_array.h>
#include <taint_analysis.h>
#include <antlr4-runtime.h>
#include <antlr4-runtime/scLexer.h>

template<typename Node>
struct Function {
    DynamicArray<Node> nodes{};
    std::vector<int> formal_parameters{};
    std::vector<int> sources{};
};

template<typename Node>
class ScCudaTransformer : public scBaseVisitor {
    std::map<std::string, int> function_counts{};
    std::vector<int>* taint_sources{};
    DynamicArray<Node>* nodes;
    int transfer_index = 0;
    std::vector<Transfer> transfers{};

    int next_var_index = RETURN_VAR_INDEX+1;
    std::map<std::string, int> var_to_index{};
    std::map<std::string, int> default_var_to_index{};

    // function nodes and vector of all formal parameter indicies
    std::map<std::string, Function<Node>> functions{};
    
    int succ_pred_index = 0;
    std::vector<int> last{};
    std::vector<int> next_last{};

    void next_layer(){
        succ_pred_index = 0;
        last = next_last;
        next_last = {};
    }

    Node& add_node(){
        int index = nodes->size();
        Node& node = nodes->emplace_back_resizable();

        for(int pred_index = 0; pred_index < last.size(); ++pred_index){
            node.predecessor_index[pred_index] = last[pred_index];
            get_nodes()[last[pred_index]].successor_index[succ_pred_index] = index;
        }
        ++succ_pred_index;

        next_last.push_back(nodes->size() - 1);

        return node;
    }

    //Use pass by value to take advantage of Copy elision and avoid copying

    int get_var_index(std::string name){
        auto it = var_to_index.find(name);
        if (it == var_to_index.end()) {
            var_to_index.emplace(std::move(name), next_var_index);
            return next_var_index++;
        }
        else {
            return it->second;
        }
    }

    Transfer& add_transfer(Node& node, int lhs_index, BitVector expression) {
        return add_transfer(node, lhs_index, expression, nodes->size() - 1);
    }

    Transfer& add_transfer(Node& node, int lhs_index, BitVector expression, int index){
        check_for_new_taint_source(expression, index);

        node.first_transfer_index = transfer_index++;
        return create_transfer(lhs_index, expression);
    }

    Transfer& add_transfer(Transfer& transfer, int lhs_index, BitVector expression, int index){
        check_for_new_taint_source(expression, index);
        
        transfer.next_transfer_index = transfer_index++;
        return create_transfer(lhs_index, expression);
    }

    void check_for_new_taint_source(BitVector expression, int index) {
        if (expression[TAINT_VAR_INDEX] && (taint_sources->size() == 0 || taint_sources->back() != index))
            taint_sources->push_back(index);
    }

    Transfer& create_transfer(int lhs_index, BitVector expression) {
        Transfer& new_transfer = transfers.emplace_back();
        new_transfer.rhs = expression.bitfield;
        new_transfer.var_index = lhs_index;
        return new_transfer;
    }

    int get_call_count(scParser::StatementcalldupingContext *ctx){
        if(ctx->INTEGER() != nullptr){
            return std::stoi(ctx->INTEGER()->getText());
        } else if(ctx->ID() != nullptr){
            return function_counts[ctx->ID()->getText()];
        }else{
            throw "Something went wrong with duplicate calls";
        }
    }

    Node& clone_function(const Function<Node>& function){
        int offset = nodes->size();
        nodes->reserve(function.nodes.size());
        for(int i = 0; i < function.nodes.size(); ++i){
            const Node& node = function.nodes[i];
            Node& new_node = nodes->emplace_back_resizable(node);
            for(int i = 0; i < 5; ++i){
                if(new_node.successor_index[i] == -1)
                    break;
                new_node.successor_index[i] += offset;
            }

            for(int i = 0; i < 5; ++i){
                if(new_node.predecessor_index[i] == -1)
                    break;
                new_node.predecessor_index[i] += offset;
            }
        }
        for (int source : function.sources) {
            taint_sources->push_back(source + offset);
        }
        return (*nodes)[offset];
    }

    public:
    ScCudaTransformer(std::map<std::string, int> function_counts) : function_counts(function_counts){
        default_var_to_index[TAINT_VAR] = TAINT_VAR_INDEX;
        default_var_to_index[RETURN_VAR] = RETURN_VAR_INDEX;
        var_to_index = default_var_to_index;
    }

    DynamicArray<Node>& get_nodes() {
        return *nodes;
    }

    std::vector<Transfer>& get_transfers(){
        return transfers;
    }

    std::vector<int>& get_sources(){
        return *taint_sources;
    }

    antlrcpp::Any visitStatementcallduping(scParser::StatementcalldupingContext *ctx) override {
        int iterations_left = get_call_count(ctx);
        while(iterations_left-- > 0){
            ctx->functionCallInit()->accept(this);
        }
        return nullptr;
    }

    antlrcpp::Any visitFunctionDef(scParser::FunctionDefContext *ctx) override
    {
        next_var_index = RETURN_VAR_INDEX+1;
        var_to_index = default_var_to_index;

        Function<Node>& function = functions[ctx->ID()->getText()];
        nodes = &function.nodes;
        taint_sources = &function.sources;

        std::vector<std::string> parameters{};
        if (ctx->opt_parameters()->parameters() != nullptr)
        {
            auto *param = ctx->opt_parameters()->parameters();
            while (param != nullptr)
            {
                function.formal_parameters.push_back(get_var_index(param->parameter()->ID()->getText()));
                param = param->parameters();
            }
        }

        Node& entry = add_node();
        next_layer();
        if (ctx->type() != nullptr)
        {
            auto out = visitChildren(ctx);
        }
        else
        {
            if (ctx->expression() != nullptr){
                throw "Shouldnt happen???";
            }

            auto out = visitChildren(ctx);

            Node& return_node = add_node(); //Empty return node
            return_node.join_mask = 0;
            next_layer();

            add_node(); // Exit node
            next_layer();
        }


        if (ctx->expression() != nullptr)
        {
            antlrcpp::Any result = ctx->expression()->accept(this);
            BitVector expression = result.as<BitVector>();

            Node& return_node = add_node();
            return_node.join_mask = 0;
            add_transfer(return_node, RETURN_VAR_INDEX, expression, nodes->size() - 1);
            next_layer();

            add_node(); // Exit node
            next_layer();

            last = {};
        }
        return nullptr;
    }
    
    virtual antlrcpp::Any visitStatementassign(scParser::StatementassignContext *ctx) override
    {
        antlrcpp::Any result = ctx->expression().back()->accept(this);
        BitVector rhs_expression = result.as<BitVector>();

        Node& assignment = add_node();
        int var_index = get_var_index(ctx->ID()->getText());
        assignment.join_mask ^= 1 << var_index;
        add_transfer(assignment, var_index, rhs_expression);
        next_layer();

        return nullptr;
    }

    virtual antlrcpp::Any visitStatementinit(scParser::StatementinitContext *ctx) override
    {
        antlrcpp::Any result = ctx->expression()->accept(this);
        BitVector expression = result.as<BitVector>();

        Node& init = add_node();
        int var_index = get_var_index(ctx->ID()->getText());
        init.join_mask ^= 1 << var_index;
        add_transfer(init, var_index, expression);
        next_layer();

        return nullptr;
    }

    virtual antlrcpp::Any visitStatementif(scParser::StatementifContext *ctx) override
    {
        antlrcpp::Any result = ctx->expression()->accept(this);
        BitVector expression = result.as<BitVector>();

        int if_node_index = nodes->size();
        Node& if_node = add_node();
        next_layer();

        //TODO: Check whether issues occur where last can contain dangling pointers after s->accept(this) call

        std::vector<int> endif;

        auto branches = ctx->statements();

        branches[0]->accept(this);
        endif.insert(endif.end(), last.begin(), last.end());

        last={if_node_index};
        next_last={};
        succ_pred_index = 1;

        branches[1]->accept(this);
        endif.insert(endif.end(), last.begin(), last.end());

        last=endif;
        next_last={};
        return nullptr;
    }

    virtual antlrcpp::Any visitExpression(scParser::ExpressionContext *ctx) override
    {
        BitVector expression(0);
        if (ctx->ID() != nullptr){
            expression.set_bit(get_var_index(ctx->ID()->getText()));
        }else if(ctx->INTEGER() != nullptr){
            // empty case
        }else if(ctx->expression() != nullptr) {
            antlrcpp::Any result = ctx->expression()->accept(this);
            expression = result.as<BitVector>();
        }
        
        if (ctx->expressionM() != nullptr && ctx->expressionM()->expression() != nullptr){
            
            antlrcpp::Any result = ctx->expressionM()->accept(this);
            expression |= result.as<BitVector>();
        }

        return expression;
    }

    virtual antlrcpp::Any visitFunctionCallInit(scParser::FunctionCallInitContext *ctx) override {
        ctx->functionCall()->accept(this);

        Node& assign_return = add_node();
        int var_index = get_var_index(ctx->ID()->getText());
        assign_return.join_mask ^= 1 << var_index;
        assign_return.join_mask ^= 1 << RETURN_VAR_INDEX;
        add_transfer(assign_return, var_index, 1<<RETURN_VAR_INDEX);
        next_layer();

        return nullptr;
    }

    virtual antlrcpp::Any visitFunctionCall(scParser::FunctionCallContext *ctx) override 
    {
        std::vector<BitVector> args;
        if(ctx->args() != nullptr){
            antlrcpp::Any result = ctx->args()->accept(this);
            args = result.as<std::vector<BitVector>>();
        }

        int func_call_index = nodes->size();
        Node& func_call = add_node(); // Add function call no op
        next_layer();
        
        auto function_id = ctx->ID()->getText();
        int entry_index = nodes->size();
        func_call.successor_index[1] = entry_index;
        Function<Node>& function = functions[function_id];
        Node& entry_node = clone_function(function);
        entry_node.join_mask = 0;

        entry_node.predecessor_index[0] = func_call_index;

        //Args might have to be reversed??
        if(args.size() > 0){
            Transfer& transfer = add_transfer(entry_node, function.formal_parameters[0], args[0], entry_index);
            
            for(int i = 1; i < args.size(); ++i){
                transfer = add_transfer(transfer, function.formal_parameters[i], args[i], entry_index);
            }
        }        

        int exit_index = nodes->size() - 1;
        last.push_back(exit_index); // Set exit node as pred for return node
        return nullptr;
    }

    virtual antlrcpp::Any visitArgs(scParser::ArgsContext *ctx) override
    {
        antlrcpp::Any expResult = ctx->expression()->accept(this);
        auto exp = expResult.as<BitVector>();

        if(ctx->args() != nullptr){
            antlrcpp::Any argResult = ctx->args()->accept(this);
            auto args = argResult.as<std::vector<BitVector>>();
            args.push_back(exp);
            return args;
        }else{
            std::vector<BitVector> args{exp};
            return args;
        }
    }

    virtual antlrcpp::Any visitWhileloop(scParser::WhileloopContext *ctx) override {
        int while_node_index = nodes->size();
        int next_pred_index = last.size();
        auto while_node = add_node();
        next_layer();

        ctx->statements()->accept(this);
        
        for(int node_index : last){
            get_nodes()[node_index].successor_index[0] = while_node_index;
            while_node.predecessor_index[next_pred_index++] = node_index;
        }
        succ_pred_index = 1;

        return nullptr;
    }

    virtual antlrcpp::Any visitExpressionM(scParser::ExpressionMContext *ctx) override
    {
        if (ctx->expression() == nullptr){
            return nullptr;
        }

        if (ctx->expressionM() != nullptr && ctx->expressionM()->expression() != nullptr){
            antlrcpp::Any rhs_result = ctx->expressionM()->accept(this);
            antlrcpp::Any lhs_result = ctx->expression()->accept(this);
            
            return lhs_result.as<BitVector>() | rhs_result.as<BitVector>();
        }else{
            antlrcpp::Any result = ctx->expression()->accept(this);
            BitVector rhs = result.as<BitVector>();
            return rhs;
        }
    }

    virtual antlrcpp::Any visitStatementinitarray(scParser::StatementinitarrayContext *ctx) override
    {
        antlrcpp::Any result = ctx->expression()->accept(this);
        BitVector arrayExpression = result.as<BitVector>();

        if (ctx->arrayelement() != nullptr)
        {
            antlrcpp::Any result = ctx->arrayelement()->accept(this);
            BitVector arrayelements = result.as<BitVector>();

            arrayExpression |= arrayelements;
        }      

        Node& array_init_node = add_node();
        int var_index = get_var_index(ctx->ID()->getText());
        array_init_node.join_mask.bitfield ^= 1 << var_index;
        add_transfer(array_init_node, var_index, arrayExpression);
        next_layer();
        
        return nullptr;
    }

    virtual antlrcpp::Any visitArrayelement(scParser::ArrayelementContext *ctx) override
    {
        if (ctx->expression() != nullptr){

            antlrcpp::Any result = ctx->expression()->accept(this);
            BitVector expression = result.as<BitVector>();

            if (ctx->arrayelement() != nullptr)
            {
                antlrcpp::Any result = ctx->arrayelement()->accept(this);
                BitVector arrayelements = result.as<BitVector>();
                
                expression |= arrayelements;   
            }

            return expression;
        }

        return BitVector(0);
    }
};

template<typename Node>
ScCudaTransformer<Node> parse_to_cuda_transformer(antlr4::ANTLRInputStream stream, std::map<std::string, int>& call_counts)
{
    scLexer lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    scParser parser(&tokens);

    parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

    ScCudaTransformer<Node> transformer(call_counts);
    parser.prog()->accept(&transformer);

    return transformer;
}