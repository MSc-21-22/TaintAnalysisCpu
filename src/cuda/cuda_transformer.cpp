#include "cuda_transformer.h"
#include "sc_transformer.h"


using namespace cuda;

CudaTransformer<bit_cuda::Node> transform_bit_cuda(std::vector<std::shared_ptr<Node>>& nodes) {
    auto variables = get_variables(nodes);
    CudaTransformer<bit_cuda::Node> transformer(nodes.size());
    for(auto &node : nodes){
        node->accept(transformer);
    }
    add_predecessors(nodes, transformer);
    return transformer;
}

CudaTransformer<cuda_worklist::Node> transform_cuda_worklist(std::vector<std::shared_ptr<Node>>& nodes) {
    auto variables = get_variables(nodes);
    CudaTransformer<cuda_worklist::Node> transformer(nodes.size());
    for(auto &node : nodes){
        node->accept(transformer);
    }
    add_neighbours(nodes, transformer);
    return transformer;
}


CudaTransformer<multi_cuda::Node> transform_multi_cuda(std::vector<std::shared_ptr<Node>>& nodes, int max_taint_sources) {
    auto variables = get_variables(nodes);
    CudaTransformer<multi_cuda::Node> transformer(nodes.size(), sizeof(multi_cuda::Node) + max_taint_sources * sizeof(BitVector));

    TaintSourceLocator taint_locator;
    int taint_index = 0;
    for(auto &node : nodes){
        node->accept(transformer);

        if(taint_locator.is_taintsource(*node)){
            if(taint_index >= max_taint_sources){
                throw "Taint index went over limit set!";
            }else{
                transformer.nodes.back().data[taint_index] = 1;
                ++taint_index;
            }
        }        
    }
    add_neighbours(nodes, transformer);
    return transformer;
}