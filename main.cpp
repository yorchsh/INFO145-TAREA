#include <bits/stdc++.h>
#include "include/vector_generation.hpp"
#include "include/binary_search.hpp"
#include "include/gap_coding.hpp"
#include "include/shannon_fano.hpp"
#include "include/csv.hpp"
#include "include/debug.hpp"

#define LINEAL_VECTOR_SIZE_IN_GIBIBYTE 0.1
#define LINEAL_VECTOR_SIZE_IN_MEBIBYTE LINEAL_VECTOR_SIZE_IN_GIBIBYTE*1024
#define LINEAL_VECTOR_SIZE_IN_KIBIBYTE LINEAL_VECTOR_SIZE_IN_MEBIBYTE*1024
#define LINEAL_VECTOR_SIZE_IN_BYTES LINEAL_VECTOR_SIZE_IN_KIBIBYTE*1024
#define LINEAL_VECTOR_SIZE LINEAL_VECTOR_SIZE_IN_BYTES/8
#define LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT 1024*1024
#define LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT

#define NORMAL_VECTOR_STANDARD_DEVIATION 1.0
#define NORMAL_VECTOR_SIZE_IN_GIBIBYTE LINEAL_VECTOR_SIZE_IN_GIBIBYTE
#define NORMAL_VECTOR_SIZE_IN_MEBIBYTE NORMAL_VECTOR_SIZE_IN_GIBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_KIBIBYTE NORMAL_VECTOR_SIZE_IN_MEBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_BYTES NORMAL_VECTOR_SIZE_IN_KIBIBYTE*1024
#define NORMAL_VECTOR_SIZE NORMAL_VECTOR_SIZE_IN_BYTES/8
#define NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT
#define NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT

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

        std::ofstream salida("salida.csv");
        /*———————————————————————————————————————————————————————————————————————
            
            %%%%%%%%%      %%%%%%      %%%%%%%%%%   %%%%%%%%%%       %%%%
            %%           %%      %%    %%           %%              %% %%
            %%           %%      %%    %%           %%            %%   %%
            %%           %%%%%%%%%%    %%%%%%%%%%   %%%%%%%%%%         %%
            %%           %%      %%            %%   %%                 %%
            %%           %%      %%            %%   %%                 %%
            %%%%%%%%%    %%      %%    %%%%%%%%%%   %%%%%%%%%%    %%%%%%%%%%%

        ———————————————————————————————————————————————————————————————————————*/


        vectorData lineal;

        std::print("CASE 1: (1/8): generate: lineal distribution vector ({} mebibytes)...",
             LINEAL_VECTOR_SIZE_IN_MEBIBYTE); std::fflush(stdout);
        auto t0 = std::chrono::high_resolution_clock::now();
        lineal.vector = vec_gen::linealVector<int64_t>(LINEAL_VECTOR_SIZE, 256);
        auto t1 = std::chrono::high_resolution_clock::now();
        
        std::println(" DONE.");
        lineal.gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();


        std::print("CASE 1: (2/8): sort: lineal distribution vector..."); std::fflush(stdout);
        t0 = std::chrono::high_resolution_clock::now();
        sort(lineal.vector.begin(), lineal.vector.end());
        t1 = std::chrono::high_resolution_clock::now();
        
        std::println(" DONE.");
        lineal.sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();


        std::print("CASE 1: (3/8): random binary search ({}n): lineal distribution vector...",
            LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT); std::fflush(stdout);
        lineal.true_results = bin_search::trueRandom(lineal.vector, 
            LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT);
        std::println(" DONE.");


        std::print("CASE 1: (4/8): random from vector binary search ({}n): lineal distribution vector...",
            LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
        lineal.select_results = bin_search::selectRandom(lineal.vector, 
            LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
        std::println(" DONE.");


        vectorData normal;

        std::print("CASE 1: (5/8): generate: normal distribution vector ({} mebibytes, {} sigma)...",
            LINEAL_VECTOR_SIZE_IN_MEBIBYTE, NORMAL_VECTOR_STANDARD_DEVIATION); std::fflush(stdout);
        
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
        std::println("(Lineal distribution vector)");
        std::println("Generation:                       {}ms", lineal_gen_time);
        std::println("Sorting:                          {}ms", lineal_sort_time);
        std::println("Generation+Sorting:               {}ms", lineal_gen_time + lineal_sort_time);
        std::println("Random binary search:             {}ms", lineal_random_binary_search_time);
        std::println("Random from vector binary search: {}ms", lineal_random_from_vector_binary_search_time);
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

        std::print("CASE 2: (1/8): generating gap_coding array from: lineal distribution vector..."); std::fflush(stdout);
        t0 = std::chrono::high_resolution_clock::now();
        gap_coding::GapArray gp_lineal(lineal.vector, 1000);
        t1 = std::chrono::high_resolution_clock::now();
        lineal.gap_coding_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
        std::println(" DONE.");

        // Código para debugear
        
        /*
        for (int i = 0; i < 10; i++) {
        std::print("{}, ", lineal.vector[i]);
        }
        std::println();

        std::println("last elements");
        for (int i = lineal.vector.size()-10; i < lineal.vector.size()-1; i++) {
            std::print("{}, ", lineal.vector[i]);
        }

        
        
        
        std::println("VECTOR[i] vs GAP CODING get(i):");
        for (int i = 0; i < 3; i++) {
            std::println("{}: {} | {}, ", i, lineal.vector[i], gp_lineal.get(i));
        }
        for (int i = 1001; i < 1004; i++) {
            std::println("{}: {} | {}, ", i, lineal.vector[i], gp_lineal.get(i));
        }
        std::println();

        std::println("CMP GAP CODE VS VECTOR");
        std::uint64_t number_finish = 0;
        for (number_finish = 0; number_finish < lineal.vector.size(); number_finish++) {
            if (lineal.vector[number_finish] != gp_lineal.get(number_finish))
                break;
        }
        std::print("vector size: {}, ", lineal.vector.size());
        std::println("number_finish: {}", number_finish);
        std::println("GAP CODING bits(i):");

        for (int i = 0; i < 10; i++) {
            print("{}: ", i);
            debug::printBits(gp_lineal.gap.array[i]);
        }

        std::println("GAPS: ");
        debug::printGaps(lineal.vector, 10);
        debug::printBitsString(gp_lineal.gap.array, 10);
        
    */

        /*———————————————————————————————————————————————————————————————————————
        CASE 3 - Compresion Shannon-Fano sobre los gaps.
        El Caso 3 usa el vector lineal y normal de los Casos 1 y 2.
        ———————————————————————————————————————————————————————————————————————*/

        std::print("CASE 3: (1/4): build Shannon-Fano: lineal distribution vector..."); std::fflush(stdout);
        auto c0 = std::chrono::high_resolution_clock::now();
        caso3::ShannonFano<std::int64_t> sf_lineal(lineal.vector, 32);
        auto c1 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        std::print("CASE 3: (2/4): search ({}n): lineal distribution vector...",
            LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
        auto c2 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT; i++)
            sf_lineal.buscar(lineal.vector[rand() % lineal.vector.size()]);
        auto c3 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        std::print("CASE 3: (3/4): build Shannon-Fano: normal distribution vector..."); std::fflush(stdout);
        auto c4 = std::chrono::high_resolution_clock::now();
        caso3::ShannonFano<std::int64_t> sf_normal(normal.vector, 32);
        auto c5 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        std::print("CASE 3: (4/4): search ({}n): normal distribution vector...",
            NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT); std::fflush(stdout);
        auto c6 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT; i++)
            sf_normal.buscar(normal.vector[rand() % normal.vector.size()]);
        auto c7 = std::chrono::high_resolution_clock::now();
        std::println(" DONE.");

        auto sf_lineal_build_time = std::chrono::duration_cast<std::chrono::milliseconds>(c1-c0).count();
        auto sf_lineal_search_time = std::chrono::duration_cast<std::chrono::milliseconds>(c3-c2).count();
        auto sf_normal_build_time = std::chrono::duration_cast<std::chrono::milliseconds>(c5-c4).count();
        auto sf_normal_search_time = std::chrono::duration_cast<std::chrono::milliseconds>(c7-c6).count();

        std::println("CASE 3:");
        std::println("(Lineal distribution vector)");
        std::println("Build (Shannon-Fano):             {}ms", sf_lineal_build_time);
        std::println("Search:                           {}ms", sf_lineal_search_time);
        std::println("Space (compressed):               {} bits", sf_lineal.espacio_bits());
        std::println("Space (explicit):                 {} bits", (std::uint64_t) lineal.vector.size() * 64);
        std::println("(Normal distribution vector)");
        std::println("Build (Shannon-Fano):             {}ms", sf_normal_build_time);
        std::println("Search:                           {}ms", sf_normal_search_time);
        std::println("Space (compressed):               {} bits", sf_normal.espacio_bits());
        std::println("Space (explicit):                 {} bits", (std::uint64_t) normal.vector.size() * 64);

        // escribimos en salida.csv
        salida << "caso3: shannon-fano\n";
        salida << "tamano,distribucion,caso,construccion_ms,busqueda_ms,n_busquedas,espacio_bits,espacio_explicito_bits\n";
        salida << lineal.vector.size() << ",lineal,3," << sf_lineal_build_time << ","
               << sf_lineal_search_time << "," << LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT << ","
               << sf_lineal.espacio_bits() << "," << (std::uint64_t) lineal.vector.size() * 64 << "\n";
        salida << normal.vector.size() << ",normal,3," << sf_normal_build_time << ","
               << sf_normal_search_time << "," << NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT << ","
               << sf_normal.espacio_bits() << "," << (std::uint64_t) normal.vector.size() * 64 << "\n";

    } else if (argc == 3 && strncmp(argv[1], "-i", 2) == 0) {
        // CASE 3 modo archivo: construye Shannon-Fano desde el CSV y busca interactivo
        std::vector<std::int64_t> datos = csv::read<std::int64_t>(argv[2]);
        if (datos.empty()) {
            std::println("El archivo no tiene numeros validos o no se pudo abrir.");
            return 1;
        }

        caso3::ShannonFano<std::int64_t> estructura(datos, 32);
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
