#pragma once

#include <bits/stdc++.h>

namespace vec_gen {
    using namespace std;

    static random_device rd;
    static mt19937 generator(rd());

    template<typename T>
    vector<T> uniformVector(int size) {
        vector<T> v;
        v.reserve(size);

        std::uniform_int_distribution<T> distribution(
            numeric_limits<T>::min(),
            numeric_limits<T>::max()
        );

        for (int i = 0; i < size; i++)
            v.push_back(distribution(generator));

        return v;
    }

    template<typename T>
    vector<T> normalVector(int size, float64_t standard_deviation) {
        std::vector<T> v;
        v.reserve(size);
        // std::normal_distribution d{5.0, 2.0};
        std::normal_distribution<float64_t> distribution(
            0.0,
            standard_deviation
        );

        for (int i = 0; i < size; i++)
            v.push_back(std::round(distribution(generator)));

        return v;
    }
}