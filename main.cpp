#include <bits/stdc++.h>
#include "include/vector_generation.hpp"
#include "include/binary_search.hpp"
#include "include/gap_coding.hpp"
// #include "include/debug.hpp"

#define UNIFORM_VECTOR_SIZE_IN_GIBIBYTE 0.1
#define UNIFORM_VECTOR_SIZE_IN_MEBIBYTE UNIFORM_VECTOR_SIZE_IN_GIBIBYTE*1024
#define UNIFORM_VECTOR_SIZE_IN_KIBIBYTE UNIFORM_VECTOR_SIZE_IN_MEBIBYTE*1024
#define UNIFORM_VECTOR_SIZE_IN_BYTES UNIFORM_VECTOR_SIZE_IN_KIBIBYTE*1024
#define UNIFORM_VECTOR_SIZE UNIFORM_VECTOR_SIZE_IN_BYTES/8
#define UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT 1024*1024
#define UNIFORM_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT

#define NORMAL_VECTOR_STANDARD_DEVIATION 1.0
#define NORMAL_VECTOR_SIZE_IN_GIBIBYTE UNIFORM_VECTOR_SIZE_IN_GIBIBYTE
#define NORMAL_VECTOR_SIZE_IN_MEBIBYTE NORMAL_VECTOR_SIZE_IN_GIBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_KIBIBYTE NORMAL_VECTOR_SIZE_IN_MEBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_BYTES NORMAL_VECTOR_SIZE_IN_KIBIBYTE*1024
#define NORMAL_VECTOR_SIZE NORMAL_VECTOR_SIZE_IN_BYTES/8
#define NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT
#define NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT

struct vectorDataStruct {
    std::vector<int64_t> vector;
    std::uint64_t gen_time; // Tiempo tomado en generar el vector
    std::uint64_t sort_time; // Tiempo tomado en ordenar el vector
    bin_search::resultsData true_results; // Resultados de la busqueda binaria de elementos al azar
    bin_search::resultsData select_results; // Resultados de la busqueda binaria de 
    std::uint64_t gap_coding_gen_time;
}; 
typedef struct vectorDataStruct vectorData;


int main(int argc, char** argv) {

    if (argc < 2 || argc > 4) {
        std::println("Usage:");
        std::println("Benchmark mode: ./main --benchmark");
        std::println("File mode: ./main -i <absolute file path>");
        std::println("Benchmark mode: Automatic");
        std::println("File mode: CSV file with user given array.");
        return 1;
    }

    if (argc == 2 && strncmp(argv[1], "--benchmark", 11) == 0) {
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");
        std::println("%%                     %%");
        std::println("%%   BENCHMARK MODE    %%");
        std::println("%%                     %%");
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");


        /*———————————————————————————————————————————————————————————————————————
            
            %%%%%%%%%      %%%%%%      %%%%%%%%%%   %%%%%%%%%%       %%%%
            %%           %%      %%    %%           %%              %% %%
            %%           %%      %%    %%           %%            %%   %%
            %%           %%%%%%%%%%    %%%%%%%%%%   %%%%%%%%%%         %%
            %%           %%      %%            %%   %%                 %%
            %%           %%      %%            %%   %%                 %%
            %%%%%%%%%    %%      %%    %%%%%%%%%%   %%%%%%%%%%    %%%%%%%%%%%

        ———————————————————————————————————————————————————————————————————————*/


        vectorData uniform;

        std::print("CASE 1: (1/8): generate: uniform distribution vector ({} mebibytes)...",
             UNIFORM_VECTOR_SIZE_IN_MEBIBYTE); std::fflush(stdout);
        auto t0 = std::chrono::high_resolution_clock::now();
        uniform.vector = vec_gen::uniformVector<int64_t>(UNIFORM_VECTOR_SIZE);
        auto t1 = std::chrono::high_resolution_clock::now();
        
        std::println(" DONE.");
        uniform.gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();


        std::print("CASE 1: (2/8): sort: uniform distribution vector..."); std::fflush(stdout);
        t0 = std::chrono::high_resolution_clock::now();
        sort(uniform.vector.begin(), uniform.vector.end());
        t1 = std::chrono::high_resolution_clock::now();
        
        std::println(" DONE.");
        uniform.sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();


        std::print("CASE 1: (3/8): random binary search ({}n): uniform distribution vector...",
            UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT); std::fflush(stdout);
        uniform.true_results = bin_search::trueRandom(uniform.vector, 
            UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT);
        std::println(" DONE.");


        std::print("CASE 1: (4/8): random from vector binary search ({}n): uniform distribution vector...",
            UNIFORM_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
        uniform.select_results = bin_search::selectRandom(uniform.vector, 
            UNIFORM_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
        std::println(" DONE.");


        vectorData normal;

        std::print("CASE 1: (5/8): generate: normal distribution vector ({} mebibytes, {} sigma)...",
            UNIFORM_VECTOR_SIZE_IN_MEBIBYTE, NORMAL_VECTOR_STANDARD_DEVIATION); std::fflush(stdout);
        
        t0 = std::chrono::high_resolution_clock::now();
        normal.vector = vec_gen::normalVector<int64_t>(NORMAL_VECTOR_SIZE, NORMAL_VECTOR_STANDARD_DEVIATION);
        t1 = std::chrono::high_resolution_clock::now();
        
        std::println(" DONE.");



        std::print("CASE 1: (6/8): sort: normal distribution vector..."); std::fflush(stdout);
        
        t0 = std::chrono::high_resolution_clock::now();
        sort(normal.vector.begin(), normal.vector.end());
        t1 = std::chrono::high_resolution_clock::now();
        
        std::println(" DONE.");



        std::print("CASE 1: (7/8): random binary search: normal distribution vector ({}n)...",
            NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT); std::fflush(stdout);
        normal.true_results = bin_search::trueRandom(normal.vector, 
            NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT);
        std::println(" DONE.");

        std::print("CASE 1: (8/8): random from vector binary search: normal distribution vector...",
            NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
        normal.select_results = bin_search::selectRandom(normal.vector,
            NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
        std::println(" DONE.");

        /*

        std::println("—RESULTS—");
        std::println("CASE 1:");
        std::println("(Uniform distribution vector)");
        std::println("Generation:                       {}ms", uniform_gen_time);
        std::println("Sorting:                          {}ms", uniform_sort_time);
        std::println("Generation+Sorting:               {}ms", uniform_gen_time + uniform_sort_time);
        std::println("Random binary search:             {}ms", uniform_random_binary_search_time);
        std::println("Random from vector binary search: {}ms", uniform_random_from_vector_binary_search_time);
        std::println("(Normal distribution vector)");
        std::println("Generation:                       {}ms", normal_gen_time);
        std::println("Sorting:                          {}ms", normal_sort_time);
        std::println("Generation+Sorting:               {}ms", normal_gen_time + normal_sort_time);
        std::println("Random binary search:             {}ms", normal_random_binary_search_time);
        std::println("Random from vector binary search: {}ms", normal_random_from_vector_binary_search_time);

        */

        /*———————————————————————————————————————————————————————————————————————
            
            %%%%%%%%%      %%%%%%      %%%%%%%%%%   %%%%%%%%%%    %%%%%%%%%%
            %%           %%      %%    %%           %%                    %%
            %%           %%      %%    %%           %%                    %%
            %%           %%%%%%%%%%    %%%%%%%%%%   %%%%%%%%%%    %%%%%%%%%%
            %%           %%      %%            %%   %%            %%
            %%           %%      %%            %%   %%            %%
            %%%%%%%%%    %%      %%    %%%%%%%%%%   %%%%%%%%%%    %%%%%%%%%%

        ———————————————————————————————————————————————————————————————————————*/

        std::print("CASE 2: (1/8): generating gap_coding array from: uniform distribution vector...");
        t0 = std::chrono::high_resolution_clock::now();
        gap_coding::GapArray gp_uniform(uniform.vector, 1000);
        t1 = std::chrono::high_resolution_clock::now();
        uniform.gap_coding_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

        // Código para debugear
        /*
        for (int i = 0; i < 10; i++) {
        std::print("{}, ", uniform.vector[i]);
        }
        std::println();

        std::println("last elements");
        for (int i = uniform.vector.size()-10; i < uniform.vector.size()-1; i++) {
            std::print("{}, ", uniform.vector[i]);
        }

        
        
        
        std::println("VECTOR[i] vs GAP CODING get(i):");
        for (int i = 0; i < 2000; i++) {
            std::println("{}: {} | {}, ", i, uniform.vector[i], gp_uniform.get(i));
        }
        std::println();

        std::println("CMP GAP CODE VS VECTOR");
        std::uint64_t number_finish = 0;
        for (number_finish = 0; number_finish < uniform.vector.size(); number_finish++) {
            if (uniform.vector[number_finish] != gp_uniform.get(number_finish))
                break;
        }
        std::print("vector size: {}, ", uniform.vector.size());
        std::println("number_finish: {}", number_finish);
        std::println("GAP CODING bits(i):");

        for (int i = 0; i < 10; i++) {
            print("{}: ", i);
            debug::printBits(gp_uniform.gap.array[i]);
        }

        std::println("GAPS: ");
        debug::printGaps(uniform.vector, 10);
        debug::printBitsString(gp_uniform.gap.array, 10);
        */



    } else if (argc == 4) {
        std::println("Complete mode");
        std::println("args: {}, {}", argv[1], argv[2]);
    }


    
    /*std::println("First 10 elements of the sorted vector: ");
    for (int i = 0; i < min(10, (int) vec.size()); i++) {
        std::print("{}, ", vec[i]);
    }
    std::println(); */
    return 0;
}