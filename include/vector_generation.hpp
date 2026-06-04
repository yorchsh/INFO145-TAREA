#pragma once

#include <bits/stdc++.h>

using namespace std;

namespace vec_gen {
    static random_device rd;
    static mt19937 generator(rd());

    template<typename T>
    vector<T> uniformVector(int size) {
        vector<T> v;
        v.reserve(size);

        uniform_int_distribution<T> distribution(
            numeric_limits<T>::min(),
            numeric_limits<T>::max()
        );

        for (int i = 0; i < size; i++)
            v.push_back(distribution(generator));

        return v;
    }

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
}