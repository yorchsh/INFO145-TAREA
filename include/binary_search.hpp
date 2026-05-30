#pragma once

#include <bits/stdc++.h>
#include "include/gap_coding.hpp"

namespace bin_search {
    using namespace std;
    
    static std::random_device rd;
    static std::mt19937 generator(rd());

    template<typename T>
    T gapBinSearch(gap_coding::GapArray<T>, int count) {
        
    }

    template<typename T>
    std::int64_t trueRandom(std::vector<T> v, int count) {
        /*  Descripción: Hace count busquedas binarias con numeros al azar en el vector v dado
            Retorna: suma de todos los tiempos (ms) en realizar *solo* las busquedas binarias
        */
        std::uniform_int_distribution<T> distribution(
            std::numeric_limits<T>::min(),
            std::numeric_limits<T>::max()
        );
        
        std::int64_t total_time = 0;

        for (int i = 0; i < count; i++) {
            T rand = distribution(generator);
            auto t0 = std::chrono::high_resolution_clock::now();
            std::binary_search(v.begin(), v.end(), rand);
            auto t1 = std::chrono::high_resolution_clock::now();
            total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count();
        }

        return total_time/(1000*1000);
    }

    template<typename T>
    std::int64_t selectRandom(std::vector<T> v, int count) {
        /*  Descripción: Hace count busquedas binarias con numeros del vector v
                         tomadas al azar en el mismo vector
            Retorna: suma de todos los tiempos (ms) en realizar *solo* las busquedas binarias
        */
        std::uniform_int_distribution<T> distribution(0, v.size());

        std::int64_t total_time = 0;

        for (int i = 0; i < count; i++) {
            T rand = distribution(generator);
            auto t0 = std::chrono::high_resolution_clock::now();
            std::binary_search(v.begin(), v.end(), rand);
            auto t1 = std::chrono::high_resolution_clock::now();
            total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count();
        }

        return total_time/(1000*1000);
    }


}