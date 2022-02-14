#include "analysis.h"

__global__ void analyze(Node nodes[], bool* has_changed){
    int node_index = threadIdx.x + blockDim.x * blockIdx.x;

    nodes[node_index].data.data = 1; // Set taint constant to true

    while(*has_changed){
        *has_changed = false;
        bool is_changed = false;
        long int new_data = 0;
        //Join
        {
            long int old_data = nodes[node_index].data.data;
            new_data = old_data;
            int pred_index = 0;
            while (nodes[node_index].predecessor_index[pred_index] != -1){
                new_data |= nodes[nodes[node_index].predecessor_index[pred_index]].data.data;
                ++pred_index;
            }

            is_changed = old_data == new_data;
        }

        //Transfer
        if(is_changed){
            int var_index = 0;
            int next_var = nodes[node_index].transfer.rhs[var_index];
            while(next_var != -1){
                if(nodes[node_index].data.data & (1 << next_var) > 0){
                    nodes[node_index].data.data |= nodes[node_index].transfer.x;
                    break;
                }
                ++var_index;
                next_var = nodes[node_index].transfer.rhs[var_index];
            }

            *has_changed = true;
        }
    }
}