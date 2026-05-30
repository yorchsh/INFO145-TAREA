#include <bits/stdc++.h>
#include "include/vector_generation.hpp"
#include "include/binary_search.hpp"
#include "include/gap_coding.hpp"

#define UNIFORM_VECTOR_SIZE_IN_GIBIBYTE 1
#define UNIFORM_VECTOR_SIZE_IN_MEBIBYTE UNIFORM_VECTOR_SIZE_IN_GIBIBYTE*1024
#define UNIFORM_VECTOR_SIZE_IN_KIBIBYTE UNIFORM_VECTOR_SIZE_IN_MEBIBYTE*1024
#define UNIFORM_VECTOR_SIZE_IN_BYTES UNIFORM_VECTOR_SIZE_IN_KIBIBYTE*1024
#define UNIFORM_VECTOR_SIZE UNIFORM_VECTOR_SIZE_IN_BYTES/8
#define UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT 1024*1024*16
#define UNIFORM_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT

#define NORMAL_VECTOR_STANDARD_DEVIATION 1.0
#define NORMAL_VECTOR_SIZE_IN_GIBIBYTE UNIFORM_VECTOR_SIZE_IN_GIBIBYTE
#define NORMAL_VECTOR_SIZE_IN_MEBIBYTE NORMAL_VECTOR_SIZE_IN_GIBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_KIBIBYTE NORMAL_VECTOR_SIZE_IN_MEBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_BYTES NORMAL_VECTOR_SIZE_IN_KIBIBYTE*1024
#define NORMAL_VECTOR_SIZE NORMAL_VECTOR_SIZE_IN_BYTES/8
#define NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT
#define NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT

int main(int argc, char** argv) {
    std::vector<std::int64_t> uniform_vector;
    std::vector<std::int64_t> normal_vector;

    std::int64_t uniform_random_binary_search_time, uniform_random_from_vector_binary_search_time,
        normal_random_binary_search_time, normal_random_from_vector_binary_search_time;

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

        std::print("CASE 1: (1/8): generate: uniform distribution vector ({} mebibytes)...",
             UNIFORM_VECTOR_SIZE_IN_MEBIBYTE); std::fflush(stdout);
        auto t0 = std::chrono::high_resolution_clock::now();
        uniform_vector = vec_gen::uniformVector<std::int64_t>(UNIFORM_VECTOR_SIZE);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");
        
        std::print("CASE 1: (2/8): sort: uniform distribution vector..."); std::fflush(stdout);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::sort(uniform_vector.begin(), uniform_vector.end());
        auto t3 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        std::print("CASE 1: (3/8): random binary search ({}n): uniform distribution vector...",
            UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT); std::fflush(stdout);
        std::int64_t uniform_random_binary_search_time = bin_search::trueRandom(uniform_vector, 
            UNIFORM_VECTOR_RANDOM_BINARY_SEARCH_COUNT);
        std::println(" DONE.");

        std::print("CASE 1: (4/8): random from vector binary search ({}n): uniform distribution vector...",
            UNIFORM_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
        std::int64_t uniform_random_from_vector_binary_search_time = bin_search::selectRandom(uniform_vector, 
            UNIFORM_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
        std::println(" DONE.");

        std::print("CASE 1: (5/8): generate: normal distribution vector ({} mebibytes, {} sigma)...", 
            UNIFORM_VECTOR_SIZE_IN_MEBIBYTE, NORMAL_VECTOR_STANDARD_DEVIATION); std::fflush(stdout);
        auto t4 = std::chrono::high_resolution_clock::now();
        std::int64_t normal_vector = vec_gen::normalVector<std::int64_t>(NORMAL_VECTOR_SIZE, NORMAL_VECTOR_STANDARD_DEVIATION);
        auto t5 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        std::print("CASE 1: (6/8): sort: normal distribution vector..."); std::fflush(stdout);
        auto t6 = std::chrono::high_resolution_clock::now();
        std::sort(normal_vector.begin(), normal_vector.end());
        auto t7 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        std::print("CASE 1: (7/8): random binary search: normal distribution vector ({}n)...",
            NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT); std::fflush(stdout);
        std::int64_t normal_random_binary_search_time= bin_search::trueRandom(normal_vector, 
            NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT);
        std::println(" DONE.");

        std::print("CASE 1: (8/8): random from vector binary search: normal distribution vector...",
            NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
        std::int64_t normal_random_from_vector_binary_search_time = bin_search::selectRandom(normal_vector,
            NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
        std::println(" DONE.");

        auto uniform_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
        auto uniform_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(t3-t2).count();
        auto normal_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t5-t4).count();
        auto normal_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(t7-t6).count();

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
        gap_coding::GapArray gp_uniform(uniform_vector, 1000);
        

    } else if (argc == 4) {
        std::println("Complete mode");
        std::println("args: {}, {}", argv[1], argv[2]);
    }


    
    /*std::println("First 10 elements of the sorted vector: ");
    for (int i = 0; i < std::min(10, (int) vec.size()); i++) {
        std::print("{}, ", vec[i]);
    }
    std::println(); */
    return 0;
}