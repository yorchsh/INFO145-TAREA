#include <bits/stdc++.h>
#include "include/vector_generation.hpp"
#include "include/binary_search.hpp"
#include "include/gap_coding.hpp"
#include "include/shannon_fano.hpp"
#include "include/csv.hpp"
#include "include/debug.hpp"

#define EPSILON 256
#define LINEAL_VECTOR_SIZE_IN_MEBIBYTE 1
#define LINEAL_VECTOR_SIZE_IN_KIBIBYTE LINEAL_VECTOR_SIZE_IN_MEBIBYTE*1024
#define LINEAL_VECTOR_SIZE_IN_BYTES LINEAL_VECTOR_SIZE_IN_KIBIBYTE*1024
#define LINEAL_VECTOR_SIZE LINEAL_VECTOR_SIZE_IN_BYTES/8
#define LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT 1024*1024
#define LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT

#define NORMAL_VECTOR_STANDARD_DEVIATION 1.0
#define NORMAL_VECTOR_SIZE_IN_MEBIBYTE LINEAL_VECTOR_SIZE_IN_MEBIBYTE
#define NORMAL_VECTOR_SIZE_IN_KIBIBYTE NORMAL_VECTOR_SIZE_IN_MEBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_BYTES NORMAL_VECTOR_SIZE_IN_KIBIBYTE*1024
#define NORMAL_VECTOR_SIZE NORMAL_VECTOR_SIZE_IN_BYTES/8
#define NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT
#define NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT


int main(int argc, char** argv) {

    if (argc == 4 && strncmp(argv[1], "--benchmark", 11) == 0 && strncmp(argv[2], "-o", 2) == 0) {
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");
        std::println("%%                     %%");
        std::println("%%   BENCHMARK MODE    %%");
        std::println("%%                     %%");
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");

        std::ofstream salida(argv[3]);

        salida << "SETTINGS" << "\n";
        salida << "RANDOM_BINARY_SEARCH_COUNT," << LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT << "\n\n";

        salida << "LINEAL_VECTOR" << "\n\n";
        salida << "size_MiB,";
        salida << "gen_time_ms,sort_time_ms,true_search_time_ms,true_search_found,true_search_not_found,select_search_time_ms,select_search_found,select_search_not_found,";
        salida << "gap_coding_gen_time,gap_coding_word_size,gap_coding_total_bits,gap_coding_sample_size_bits,gap_coding_search_time_ms,";
        salida << "shannon_fano_gen_time_ms,shannon_fano_search_time_ms,space_bits_compressed,space_bits_explicit";
        salida << "\n";

        std::vector<std::uint64_t> VECTOR_SIZES_MEBIBYTE = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};


        for (auto& vector_size: VECTOR_SIZES_MEBIBYTE) {
            salida << vector_size << ",";

            std::print("CASE 1: (1/4): generate: lineal distribution vector ({} mebibytes)...",
                vector_size); std::fflush(stdout);
            
            auto t0 = std::chrono::high_resolution_clock::now();
            auto lineal_vector = vec_gen::linealVector<int64_t>(vector_size * LINEAL_VECTOR_SIZE, EPSILON);
            auto t1 = std::chrono::high_resolution_clock::now();
            std::println(" DONE.");
            auto lineal_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

            std::print("CASE 1: (2/4): sort: lineal distribution vector..."); std::fflush(stdout);
            t0 = std::chrono::high_resolution_clock::now();
            sort(lineal_vector.begin(), lineal_vector.end());
            t1 = std::chrono::high_resolution_clock::now();
            std::println(" DONE.");
            auto lineal_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

            std::print("CASE 1: (3/4): random binary search ({}n): lineal distribution vector...",
            LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT); std::fflush(stdout);
            auto lineal_true_results = bin_search::trueRandom(lineal_vector, 
                LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT);
            std::println(" DONE.");

            std::print("CASE 1: (4/4): random from vector binary search ({}n): lineal distribution vector...",
            LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
            auto lineal_select_results = bin_search::selectRandom(lineal_vector, 
                LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
            std::println(" DONE.");

            salida << lineal_gen_time << ",";
            salida << lineal_sort_time << ",";
            salida << lineal_true_results.time << ",";
            salida << lineal_true_results.found << ",";
            salida << lineal_true_results.not_found << ",";
            salida << lineal_select_results.time << ",";
            salida << lineal_select_results.found << ",";
            salida << lineal_select_results.not_found << ",";
            salida << "n";

            std::print("CASE 2: (1/3): generating gap_coding array from: lineal distribution vector..."); std::fflush(stdout);
            t0 = std::chrono::high_resolution_clock::now();
            gap_coding::GapArray lineal_gap_coding(lineal_vector);
            t1 = std::chrono::high_resolution_clock::now();
            auto lineal_gap_coding_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
            std::println(" DONE.");

            salida << lineal_gap_coding_gen_time << ",";
            salida << lineal_gap_coding.gap.word_size << ",";
            salida << lineal_gap_coding.gap.word_size * lineal_vector.size() << ",";
            salida << lineal_gap_coding.sample.size * 64 << ",";

            std::print("CASE 3: (1/2): build Shannon-Fano: lineal distribution vector..."); std::fflush(stdout);
            t0 = std::chrono::high_resolution_clock::now();
            caso3::ShannonFano<std::int64_t> sf_lineal(lineal_vector);
            t1 = std::chrono::high_resolution_clock::now();
            std::println(" DONE.");
            auto sf_lineal_build_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

            std::print("CASE 3: (2/2): search ({}n): lineal distribution vector...",
            LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
            t0 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT; i++)
                sf_lineal.buscar(lineal_vector[rand() % lineal_vector.size()]);
            t1 = std::chrono::high_resolution_clock::now();
            std::println(" DONE.");
            auto sf_lineal_search_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

            salida << sf_lineal_build_time << ",";
            salida << sf_lineal_search_time << ",";
            salida << sf_lineal.espacio_bits() << ","; 
            salida << (std::uint64_t) lineal_vector.size() * 64;
            salida << "\n";
            

        }

    } else if (argc == 5 && strncmp(argv[1], "-i", 2) == 0 && strncmp(argv[3], "-o", 2) == 0) {
        // CASE 3 modo archivo: construye Shannon-Fano desde el CSV y busca interactivo
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");
        std::println("%%                     %%");
        std::println("%%      FILE MODE      %%");
        std::println("%%                     %%");
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");
        
        std::vector<std::int64_t> datos = csv::read<std::int64_t>(argv[2]);
        if (datos.empty()) {
            std::println("El archivo no tiene numeros validos o no se pudo abrir.");
            return 1;
        }

        caso3::ShannonFano<std::int64_t> estructura(datos);
        std::println("Construido con {} elementos. Ingrese valores a buscar, 'q' para salir:",
            datos.size());

        std::string linea;
        while (std::getline(std::cin, linea)) {
            
            if (linea == "q" || linea == "Q") break;
            if (linea.empty()) continue;

            std::int64_t x = std::strtoll(linea.c_str(), nullptr, 10);
            auto a = std::chrono::high_resolution_clock::now();
            std::int64_t pos = estructura.buscar(x);
            auto b = std::chrono::high_resolution_clock::now();
            auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count();

            if (pos >= 0)
                std::println("{}: encontrado en posicion {} ({} ns)", x, pos, ns);
            else
                std::println("{}: no encontrado ({} ns)", x, ns);
        }
        
    } else {
        std::println("Usage:");
        std::println("Benchmark mode: ./main --benchmark -o <absolute file path>");
        std::println("File mode: ./main -i <absolute file path> -o <absolute file path>");
        std::println("Where -o is the output of the program");
        std::println("Benchmark mode: Automatic");
        std::println("File mode: CSV file with user given array.");
        return 1;
    }


    
    /*std::println("First 10 elements of the sorted vector: ");
    for (int i = 0; i < min(10, (int) vec.size()); i++) {
        std::print("{}, ", vec[i]);
    }
    std::println(); */
    return 0;
}
