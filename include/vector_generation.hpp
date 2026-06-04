#pragma once

#include <bits/stdc++.h>

using namespace std;

namespace vec_gen {
    static random_device rd;
    static mt19937 generator(rd());

    template<typename T>
    vector<T> normalVector(int size, float64_t standard_deviation) {
        vector<T> v;
        v.reserve(size);
        // normal_distribution d{5.0, 2.0};
        normal_distribution<float64_t> distribution(
            0.0,
            standard_deviation
        );

        for (int i = 0; i < size; i++)
            v.push_back(round(distribution(generator)));

        return v;
    }
    
    template<typename T>
    std::vector<T> linealVector(int size, T epsilon) {
        std::vector<T> v;
        v.reserve(size);

        std::uniform_int_distribution<T> gap(0, epsilon - 1);

        T actual = 0;
        for (int i = 0; i < size; i++) {
            actual += gap(generator);
            v.push_back(actual);
        }

        return v;
    }
}
