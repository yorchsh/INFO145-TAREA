#include <bits/stdc++.h>
#include "include/vector_generation.hpp"
#include "include/binary_search.hpp"

#define UNIFORM_VECTOR_SIZE_IN_GIBIBYTE 1
#define UNIFORM_VECTOR_SIZE_IN_MEBIBYTE UNIFORM_VECTOR_SIZE_IN_GIBIBYTE*1024
#define UNIFORM_VECTOR_SIZE_IN_KIBIBYTE UNIFORM_VECTOR_SIZE_IN_MEBIBYTE*1024
#define UNIFORM_VECTOR_SIZE_IN_BYTES UNIFORM_VECTOR_SIZE_IN_KIBIBYTE*1024
#define UNIFORM_VECTOR_SIZE UNIFORM_VECTOR_SIZE_IN_BYTES/8

#define NORMAL_VECTOR_STANDARD_DEVIATION 1.0
#define NORMAL_VECTOR_SIZE_IN_GIBIBYTE 1
#define NORMAL_VECTOR_SIZE_IN_MEBIBYTE UNIFORM_VECTOR_SIZE_IN_GIBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_KIBIBYTE UNIFORM_VECTOR_SIZE_IN_MEBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_BYTES UNIFORM_VECTOR_SIZE_IN_KIBIBYTE*1024
#define NORMAL_VECTOR_SIZE UNIFORM_VECTOR_SIZE_IN_BYTES/8

int main(int argc, char** argv) {
    std::vector<int64_t> uniform_vector;
    std::vector<int64_t> normal_vector;
    std::chrono::_V2::system_clock::time_point t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;

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

        std::print("CASE 1: (1/10): generate: uniform distribution vector ({} mebibytes)...", UNIFORM_VECTOR_SIZE_IN_MEBIBYTE);
        std::fflush(stdout);
        t0 = std::chrono::high_resolution_clock::now();
        uniform_vector = vec_gen::uniformVector<std::int64_t>(UNIFORM_VECTOR_SIZE);
        t1 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");
        
        std::print("CASE 1: (2/10): sort: uniform distribution vector..."); std::fflush(stdout);
        t2 = std::chrono::high_resolution_clock::now();
        std::sort(uniform_vector.begin(), uniform_vector.end());
        t3 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        std::print("CASE 1: (3/10): generate: normal distribution vector ({} mebibytes, {} sigma)...", UNIFORM_VECTOR_SIZE_IN_MEBIBYTE,
                    NORMAL_VECTOR_STANDARD_DEVIATION); std::fflush(stdout);
        t4 = std::chrono::high_resolution_clock::now();
        normal_vector = vec_gen::normalVector<std::int64_t>(NORMAL_VECTOR_SIZE, NORMAL_VECTOR_STANDARD_DEVIATION);
        t5 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        std::print("CASE 1: (4/10): sort: normal distribution vector..."); std::fflush(stdout);
        t6 = std::chrono::high_resolution_clock::now();
        std::sort(normal_vector.begin(), normal_vector.end());
        t7 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");


    } else if (argc == 4) {
        std::println("Complete mode");
        std::println("args: {}, {}", argv[1], argv[2]);
    }

    auto uniform_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
    auto uniform_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(t3-t2);
    auto normal_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t5-t4);
    auto normal_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(t7-t6);


    std::println("—RESULTS—");
    std::println("CASE 1:");
    std::println("(Uniform distribution vector)");
    std::println("Generation:           {}ms", uniform_gen_time.count());
    std::println("Sorting:              {}ms", uniform_sort_time.count());
    std::println("Generation+Sorting:   {}ms", uniform_gen_time.count() + uniform_sort_time.count());
    std::println("(Normal distribution vector)");
    std::println("Generation:           {}ms", normal_gen_time.count());
    std::println("Sorting:              {}ms", normal_sort_time.count());
    std::println("Generation+Sorting:   {}ms", normal_gen_time.count() + normal_sort_time.count());
    
    /*std::println("First 10 elements of the sorted vector: ");
    for (int i = 0; i < std::min(10, (int) vec.size()); i++) {
        std::print("{}, ", vec[i]);
    }
    std::println(); */
    return 0;
}