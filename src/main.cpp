#include <iostream>
#include <string>
#include "antlr4-runtime/scLexer.h"
#include "antlr4-runtime/scParser.h"
#include "transforms.h"
#include "worklist.h"
#include "taint_analysis.h"
#include "multi_taint_analysis.h"
#include "digraph.h"
#include "matrix_analysis.h"
#include <cubool.h>
#include <stdio.h>

#define CHECK(f) { cuBool_Status s = f; if (s != CUBOOL_STATUS_SUCCESS) return s; }

int test_cubool(){
        cuBool_Matrix A;
    cuBool_Matrix TC;

    /* System may not provide Cuda compatible device */
    CHECK(cuBool_Initialize(CUBOOL_HINT_NO));

    /* Input graph G */

    /*  -> (1) ->           */
    /*  |       |           */
    /* (0) --> (2) <--> (3) */

    /* Adjacency matrix in sparse format  */
    cuBool_Index n = 4;
    cuBool_Index e = 5;
    cuBool_Index rows[] = { 0, 0, 1, 2, 3 };
    cuBool_Index cols[] = { 1, 2, 2, 3, 2 };

    /* Create matrix */
    CHECK(cuBool_Matrix_New(&A, n, n));

    /* Fill the data */
    CHECK(cuBool_Matrix_Build(A, rows, cols, e, CUBOOL_HINT_VALUES_SORTED));

    /* Now we have created the following matrix */

    /*    [0][1][2][3]
    /* [0] .  1  1  .  */
    /* [1] .  .  1  .  */
    /* [2] .  .  .  1  */
    /* [3] .  .  1  .  */

    /* Create result matrix from source as copy */
    CHECK(cuBool_Matrix_Duplicate(A, &TC));

    /* Query current number on non-zero elements */
    cuBool_Index total = 0;
    cuBool_Index current;
    CHECK(cuBool_Matrix_Nvals(TC, &current));

    /* Loop while values are added */
    while (current != total) {
        total = current;

        /** Transitive closure step */
        CHECK(cuBool_MxM(TC, TC, TC, CUBOOL_HINT_ACCUMULATE));
        CHECK(cuBool_Matrix_Nvals(TC, &current));
    }

    /** Get result */
    cuBool_Index tc_rows[16], tc_cols[16];
    CHECK(cuBool_Matrix_ExtractPairs(TC, tc_rows, tc_cols, &total));

    /** Now tc_rows and tc_cols contain (i,j) pairs of the result G_tc graph */

    /*    [0][1][2][3]
    /* [0] .  1  1  1  */
    /* [1] .  .  1  1  */
    /* [2] .  .  1  1  */
    /* [3] .  .  1  1  */

    /* Output result size */
    printf("Nnz(tc)=%lli\n", (unsigned long long) total);

    for (cuBool_Index i = 0; i < total; i++)
        printf("(%u,%u) ", tc_rows[i], tc_cols[i]);

    /* Release resources */
    CHECK(cuBool_Matrix_Free(A));
    CHECK(cuBool_Matrix_Free(TC));

    /* Release library */
    return cuBool_Finalize() != CUBOOL_STATUS_SUCCESS;
}

void print_result(std::set<std::string>& result, std::ostream& stream){
    stream << "\\n{ ";
    for (auto& x : result){
        if (x!="£"){
            stream << x << " ";
        }
    }
    stream << "}";
}

void cpu_analysis(ScTransformer<std::set<std::string>> program){
    TaintAnalyzer analyzer;
    worklist(program.nodes, analyzer);

    //print_digraph_with_result<std::set<std::string>>(program.nodes, std::cout, print_result);
    print_digraph_subgraph(program.entryNodes, std::cout, print_result, "main");
}

void cpu_multi_taint_analysis(ScTransformer<SourcedTaintState> program){
    MultiTaintAnalyzer analyzer;
    worklist(program.nodes, analyzer);

    print_digraph_subgraph(program.entryNodes, std::cout, print_taint_source, "main");
}

int main(int argc, char *argv[]){
    return test_cubool();

    if(argc > 1){

        bool gpu_flag = false, multi_taint_flag = false;
        for (int i = 1; i < argc; i++)
        {
            char* arg = argv[i];
            if(strcmp(arg, "--gpu") == 0 || strcmp(arg, "-g") == 0){
                gpu_flag = true;
            }
            if(strcmp(arg, "--multi") == 0 || strcmp(arg, "-m") == 0){
                multi_taint_flag = true;
            }
        }

        antlr4::ANTLRFileStream csfile;
        csfile.loadFromFile(argv[argc-1]);
        antlr4::ANTLRInputStream prog(csfile);

        if(gpu_flag){
            std::cout << "Running analysis using GPU" << std::endl;
            auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
            gpu_analysis(program.nodes);
            print_digraph_subgraph(program.entryNodes, std::cout, print_result, "main");
        }else{
            if(multi_taint_flag){
                std::cout << "Running multi-taint analysis using CPU" << std::endl;
                auto program = parse_to_cfg_transformer<SourcedTaintState>(prog);
                cpu_multi_taint_analysis(program);
            }else{
                std::cout << "Running analysis using CPU" << std::endl;
                auto program = parse_to_cfg_transformer<std::set<std::string>>(prog);
                cpu_analysis(program);
            }
        }

    }
    return 0;
}