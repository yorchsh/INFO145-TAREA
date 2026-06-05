#pragma once

#include <bits/stdc++.h>
#include "binary_search.hpp"

namespace binary_search_sf {

    // Predecesor: retorna el indice de la mayor v[i] <= x,
    // o -1 si x es menor que todo el vector.
    template<typename T>
    std::int64_t vecSearch(std::vector<T>& v, T x) {
        auto it = std::upper_bound(v.begin(), v.end(), x);
        return (it - v.begin()) - 1;
    }

    // Hace count busquedas en sf usando elementos al azar tomados del vector v.
    // ShannonFanoType es un parametro de template para evitar dependencia circular
    // con shannon_fano.hpp (que incluye este archivo).
    template<typename ShannonFanoType, typename T>
    bin_search::resultsData sfSelectRandom(ShannonFanoType& sf, std::vector<T>& v, int count) {
        bin_search::resultsData results;
        std::uniform_int_distribution<std::size_t> dist(0, v.size() - 1);

        for (int i = 0; i < count; i++) {
            T val = v[dist(bin_search::generator)];
            auto t0 = std::chrono::high_resolution_clock::now();
            std::int64_t index = sf.buscar(val);
            auto t1 = std::chrono::high_resolution_clock::now();
            results.time += std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();

            if (index != -1)
                results.found++;
            else
                results.not_found++;
        }

        results.time /= 1000 * 1000;
        return results;
    }

}
