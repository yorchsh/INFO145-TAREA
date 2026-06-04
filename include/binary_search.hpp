#pragma once

#include <bits/stdc++.h>
#include "gap_coding.hpp"

namespace bin_search {
    using namespace std;

    struct resultsDataStruct {
        uint64_t time = 0; // Tiempo de todas las busquedas
        uint64_t found = 0; // Veces que se encontro el elemento en el vector 
        uint64_t not_found = 0; // Veces que no fue encontrado el elemento en el vector
    }; typedef struct resultsDataStruct resultsData;

    static random_device rd;
    static mt19937 generator(rd());

    template<typename T>
    T gapBinSearch(gap_coding::GapArray<T>& , int count) {
        
    }

    template<typename T>
    resultsData trueRandom(vector<T>& v, int count) {
        // Hace count busquedas binarias con numeros al azar en el vector v dado
        resultsData results;
        uniform_int_distribution<T> distribution(
            numeric_limits<T>::min(),
            numeric_limits<T>::max()
        );
        
        for (int i = 0; i < count; i++) {
            T rand = distribution(generator);
            auto t0 = chrono::high_resolution_clock::now();
            bool found = binary_search(v.begin(), v.end(), rand);
            auto t1 = chrono::high_resolution_clock::now();
            results.time += chrono::duration_cast<chrono::nanoseconds>(t1-t0).count();
            
            if (found)
                results.found++;
            else
                results.not_found++;
        }
        
        results.time /= 1000*1000; // Pasar a milisegundos
        return results;
    }

    template<typename T>
    resultsData selectRandom(vector<T>& v, int count) {
        // Descripción: Hace count busquedas binarias con numeros del vector v tomadas al azar en el mismo vector
        
        resultsData results;
        uniform_int_distribution<T> distribution(0, v.size());

        for (int i = 0; i < count; i++) {
            T rand = distribution(generator);
            auto t0 = chrono::high_resolution_clock::now();
            bool found = binary_search(v.begin(), v.end(), rand);
            auto t1 = chrono::high_resolution_clock::now();
            results.time += chrono::duration_cast<chrono::nanoseconds>(t1-t0).count(); 
            
            if (found)
                results.found++;
            else
                results.not_found++;
        }

        results.time /= 1000*1000; // Pasar a milisegundos
        return results;
    }


}