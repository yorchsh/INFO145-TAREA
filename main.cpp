#include <bits/stdc++.h>
#include "include/linea_base.hpp"
#include "include/vector_generation.hpp"
#include "include/binary_search.hpp"
#include "include/gap_coding.hpp"
#include "include/shannon_fano.hpp"
#include "include/csv.hpp"

#define EPSILON 256
#define CPU_WORD_SIZE 64
#define LINEAL_VECTOR_SIZE_IN_MEBIBYTE 1
#define LINEAL_VECTOR_SIZE_IN_KIBIBYTE LINEAL_VECTOR_SIZE_IN_MEBIBYTE*1024
#define LINEAL_VECTOR_SIZE_IN_BYTES LINEAL_VECTOR_SIZE_IN_KIBIBYTE*1024
#define LINEAL_VECTOR_SIZE LINEAL_VECTOR_SIZE_IN_BYTES/8
#define LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT 512*512
#define LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT

#define NORMAL_VECTOR_SIZE_IN_MEBIBYTE LINEAL_VECTOR_SIZE_IN_MEBIBYTE
#define NORMAL_VECTOR_SIZE_IN_KIBIBYTE NORMAL_VECTOR_SIZE_IN_MEBIBYTE*1024
#define NORMAL_VECTOR_SIZE_IN_BYTES NORMAL_VECTOR_SIZE_IN_KIBIBYTE*1024
#define NORMAL_VECTOR_SIZE NORMAL_VECTOR_SIZE_IN_BYTES/8
#define NORMAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT
#define NORMAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT



void writeHeader(std::ofstream& salida) {
    salida << "gen_time_ms,sort_time_ms,true_search_time_ms,true_search_found,true_search_not_found,select_search_time_ms,select_search_found,select_search_not_found,";
    salida << "gc_gen_time,gc_word_size,gc_total_bits,gc_sample_size_bits,"
            << "gc_true_search_time_ms,gc_true_search_found,gc_true_search_not_found,"
            << "gc_select_search_time_ms,gc_select_search_found,gc_select_search_not_found,";
    salida << "sf_gen_time_ms,sf_search_time_ms,space_bits_compressed,space_bits_explicit";
}

template <typename T>
void benchmark(std::ofstream& salida, std::vector<T>& v, std::string vector_name, std::uint64_t vector_size_MiB) {

    std::print("    CASE 1: (2/4): sort: {} distribution vector...", vector_name); std::fflush(stdout);
    auto t0 = std::chrono::high_resolution_clock::now();
    sort(v.begin(), v.end());
    auto t1 = std::chrono::high_resolution_clock::now();
    std::println(" DONE.");
    auto v_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

    std::print("    CASE 1: (3/4): random binary search ({}n): {} distribution vector...",
    LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT, vector_name); std::fflush(stdout);
    auto v_true_results = bin_search::trueRandom(v, 
        LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT);
    std::println(" DONE.");

    std::print("    CASE 1: (4/4): random from vector binary search ({}n): {} distribution vector...",
    LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT, vector_name); std::fflush(stdout);
    auto v_select_results = bin_search::selectRandom(v, 
        LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
    std::println(" DONE.");

    salida << v_sort_time << ",";
    salida << v_true_results.time << ",";
    salida << v_true_results.found << ",";
    salida << v_true_results.not_found << ",";
    salida << v_select_results.time << ",";
    salida << v_select_results.found << ",";
    salida << v_select_results.not_found << ",";

    std::print("    CASE 2: (1/3): generating gap_coding array from: {} distribution vector...", vector_name); std::fflush(stdout);
    t0 = std::chrono::high_resolution_clock::now();
    gap_coding::GapArray v_gap_coding(v);
    t1 = std::chrono::high_resolution_clock::now();
    auto v_gap_coding_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
    std::println(" DONE.");

    std::print("    CASE 2: (2/3): random binary search: {} gap_coding...", vector_name); std::fflush(stdout);
    auto v_gap_coding_true_results = bin_search::trueRandom(v_gap_coding, 
        LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
    std::println(" DONE.");

    std::print("    CASE 2: (3/3): random from gap_coding binary search: {} gap_coding...", vector_name); std::fflush(stdout);
    auto v_gap_coding_select_results = bin_search::selectRandom(v_gap_coding, 
        LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
    std::println(" DONE.");
    
    salida << v_gap_coding_gen_time << ",";
    salida << v_gap_coding.gap.word_size << ",";
    salida << v_gap_coding.gap.word_size * v.size() << ",";
    salida << v_gap_coding.sample.size * CPU_WORD_SIZE << ",";
    salida << v_gap_coding_true_results.time << ",";
    salida << v_gap_coding_true_results.found << ",";
    salida << v_gap_coding_true_results.not_found << ",";
    salida << v_gap_coding_select_results.time << ",";
    salida << v_gap_coding_select_results.found << ",";
    salida << v_gap_coding_select_results.not_found << ",";

            
    std::print("    CASE 3: (1/2): build Shannon-Fano: {} distribution vector...", vector_name); std::fflush(stdout);
    t0 = std::chrono::high_resolution_clock::now();
    caso3::ShannonFano<std::int64_t> sf_v(v);
    t1 = std::chrono::high_resolution_clock::now();
    std::println(" DONE.");
    auto sf_v_build_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

    std::print("    CASE 3: (2/2): search ({}n): {} distribution vector...",
    LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT, vector_name); std::fflush(stdout);
    auto sf_v_results = binary_search_sf::sfSelectRandom(sf_v, v, LINEAL_VECTOR_RANDOM_FROM_VECTOR_BINARY_SEARCH_COUNT);
    std::println(" DONE.");
    auto sf_v_search_time = sf_v_results.time;

    salida << sf_v_build_time << ",";
    salida << sf_v_search_time << ",";
    salida << sf_v.espacio_bits() << ","; 
    salida << (std::uint64_t) v.size() * 64;
            
    salida << "\n";
            
}


int main(int argc, char** argv) {
    bool es_benchmark = (argc == 2 && strncmp(argv[1], "--benchmark", 11) == 0) ||
                        (argc == 4 && strncmp(argv[1], "--benchmark", 11) == 0 && strncmp(argv[2], "-o", 2) == 0);

    if (es_benchmark) {
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");
        std::println("%%                     %%");
        std::println("%%   BENCHMARK MODE    %%");
        std::println("%%                     %%");
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");

        const std::string output_path = (argc == 4) ? argv[3] : "salida.csv";
        std::println("Salida: {}", output_path);
        std::ofstream salida(output_path);

        salida << "SETTINGS" << "\n";
        salida << "RANDOM_BINARY_SEARCH_COUNT," << LINEAL_VECTOR_RANDOM_BINARY_SEARCH_COUNT << "\n\n";

        salida << "LINEAL_VECTOR" << "\n";
        salida << "size_MiB,";
        writeHeader(salida);
        salida << "\n";
        // ~10^6, ~10^7, ~10^8 elementos (8 bytes/elem). Ajustar segun RAM y tiempo disponibles.
        std::vector<std::uint64_t> VECTOR_SIZES_MEBIBYTE = {8, 76, 763};

        for (auto& vector_size_MiB: VECTOR_SIZES_MEBIBYTE) {
            salida << vector_size_MiB << ",";

            std::print("CASE 1: (1/4): generate: lineal distribution vector ({} mebibytes)...",
                vector_size_MiB); std::fflush(stdout);
            
            auto t0 = std::chrono::high_resolution_clock::now();
            auto lineal_vector = vec_gen::linealVector<int64_t>(vector_size_MiB * LINEAL_VECTOR_SIZE, EPSILON);
            auto t1 = std::chrono::high_resolution_clock::now();
            std::println(" DONE.");
            auto lineal_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

            salida << lineal_gen_time << ",";
            benchmark(salida, lineal_vector, "lineal", vector_size_MiB);

        }

        salida << "\n\n";

        salida << "NORMAL_VECTOR" << "\n";
        salida << "size_MiB,standard_deviation_sigma,";
        writeHeader(salida);
        salida << "\n";

        std::vector<std::float64_t> STANDARD_DEVIATIONS = {1, 2, 3, 4};

        // std::vector<std::float64_t> STANDARD_DEVIATIONS = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

        for (auto& vector_size_MiB: VECTOR_SIZES_MEBIBYTE) {
            for (auto& standard_deviation: STANDARD_DEVIATIONS) {
                salida << vector_size_MiB << ",";
                salida << standard_deviation << ",";

                std::print("CASE 1: (1/4): generate: normal distribution vector ({} mebibytes, {} sigma)...",
                    vector_size_MiB, standard_deviation); std::fflush(stdout);
                
                auto t0 = std::chrono::high_resolution_clock::now();
                auto lineal_vector = vec_gen::normalVector<int64_t>(vector_size_MiB * LINEAL_VECTOR_SIZE, standard_deviation);
                auto t1 = std::chrono::high_resolution_clock::now();
                std::println(" DONE.");
                auto lineal_gen_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();

                salida << lineal_gen_time << ",";
                benchmark(salida, lineal_vector, "normal", vector_size_MiB);
            }

        }

        

    } else if ((argc == 5 && strncmp(argv[1], "-i", 2) == 0 && strncmp(argv[3], "-c", 2) == 0) ||
               (argc == 3 && strncmp(argv[1], "-i", 2) == 0)) {
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");
        std::println("%%                     %%");
        std::println("%%      FILE MODE      %%");
        std::println("%%                     %%");
        std::println("%%%%%%%%%%%%%%%%%%%%%%%%%");

        int caso = 0;
        if (argc == 5) {
            caso = std::atoi(argv[4]);
        } else {
            std::println("Seleccione estructura a usar:");
            std::println("  1: Representacion explicita (busqueda binaria estandar)");
            std::println("  2: Gap Coding");
            std::println("  3: Shannon-Fano");
            std::string eleccion;
            std::getline(std::cin, eleccion);
            caso = std::atoi(eleccion.c_str());
        }

        if (caso < 1 || caso > 3) {
            std::println("Caso invalido: ingrese 1, 2 o 3.");
            return 1;
        }

        std::vector<std::int64_t> datos = csv::read<std::int64_t>(argv[2]);
        if (datos.empty()) {
            std::println("El archivo no tiene numeros validos o no se pudo abrir.");
            return 1;
        }
        std::sort(datos.begin(), datos.end());

        auto buscar_e_imprimir = [](std::int64_t x, std::int64_t pos, long long ns) {
            if (pos >= 0)
                std::println("{}: encontrado en posicion {} ({} ns)", x, pos, ns);
            else
                std::println("{}: no encontrado ({} ns)", x, ns);
        };

        std::string linea;

        if (caso == 1) {
            std::println("Caso 1 (busqueda binaria explicita). {} elementos. Ingrese valores, 'q' para salir:", datos.size());
            while (std::getline(std::cin, linea)) {
                if (linea == "q" || linea == "Q") break;
                if (linea.empty()) continue;
                std::int64_t x = std::strtoll(linea.c_str(), nullptr, 10);
                auto a = std::chrono::high_resolution_clock::now();
                auto it = std::lower_bound(datos.begin(), datos.end(), x);
                std::int64_t pos = (it != datos.end() && *it == x) ? (std::int64_t)(it - datos.begin()) : -1;
                auto b = std::chrono::high_resolution_clock::now();
                buscar_e_imprimir(x, pos, std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count());
            }

        } else if (caso == 2) {
            std::print("Construyendo Gap Coding..."); std::fflush(stdout);
            gap_coding::GapArray<std::int64_t> estructura(datos);
            std::println(" listo. {} elementos. Ingrese valores, 'q' para salir:", datos.size());
            while (std::getline(std::cin, linea)) {
                if (linea == "q" || linea == "Q") break;
                if (linea.empty()) continue;
                std::int64_t x = std::strtoll(linea.c_str(), nullptr, 10);
                auto a = std::chrono::high_resolution_clock::now();
                std::int64_t pos = bin_search::gapSearch(estructura, x);
                auto b = std::chrono::high_resolution_clock::now();
                buscar_e_imprimir(x, pos, std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count());
            }

        } else {
            std::print("Construyendo Shannon-Fano..."); std::fflush(stdout);
            caso3::ShannonFano<std::int64_t> estructura(datos);
            std::println(" listo. {} elementos. Ingrese valores, 'q' para salir:", datos.size());
            while (std::getline(std::cin, linea)) {
                if (linea == "q" || linea == "Q") break;
                if (linea.empty()) continue;
                std::int64_t x = std::strtoll(linea.c_str(), nullptr, 10);
                auto a = std::chrono::high_resolution_clock::now();
                std::int64_t pos = estructura.buscar(x);
                auto b = std::chrono::high_resolution_clock::now();
                buscar_e_imprimir(x, pos, std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count());
            }
        }

    } else {
        std::println("Uso:");
        std::println("  Benchmark: ./main --benchmark");
        std::println("             ./main --benchmark -o <archivo_salida.csv>   (salida.csv por defecto)");
        std::println("  Archivo:   ./main -i <archivo.csv>");
        std::println("             ./main -i <archivo.csv> -c <caso>");
        std::println("             donde <caso> es 1 (explicito), 2 (gap coding) o 3 (shannon-fano)");
        std::println("Numeros aceptados: int64_t [-9223372036854775808, 9223372036854775807] (strtoll)");
        return 1;
    }

    return 0;
}
