#pragma once

#include <bits/stdc++.h>

namespace vec_gen {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    template<typename T>
    std::vector<T> uniformVector(int size) {
        std::vector<T> v;
        v.reserve(size);

        std::uniform_int_distribution<T> distribution(
            std::numeric_limits<T>::min(),
            std::numeric_limits<T>::max()
        );

        for (int i = 0; i < size; i++)
            v.push_back(distribution(generator));

        return v;
    }

    template<typename T>
    std::vector<T> normalVector(int size, std::float64_t standard_deviation) {
        std::vector<T> v;
        v.reserve(size);
        // std::normal_distribution d{5.0, 2.0};
        std::normal_distribution<std::float64_t> distribution(
            0.0,
            standard_deviation
        );

        for (int i = 0; i < size; i++)
            v.push_back(std::round(distribution(generator)));

        return v;
    }
    
    // esto debemos usarlo en todos los Casos
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