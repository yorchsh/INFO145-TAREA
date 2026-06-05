#pragma once

// Caso 1: (Linea Base).

#include "binary_search.hpp"

namespace caso1 {

    template<typename T>
    void construir(std::vector<T>& v) {
        std::sort(v.begin(), v.end());
    }

    template<typename T>
    std::int64_t buscar(std::vector<T>& v, T x) {
        auto it = std::lower_bound(v.begin(), v.end(), x);
        if (it != v.end() && *it == x)
            return static_cast<std::int64_t>(it - v.begin());
        return -1;
    }

    // Espacio en bits del arreglo explicito: un elemento de sizeof(T)*8 bits por valor.
    template<typename T>
    std::uint64_t espacio_bits(const std::vector<T>& v) {
        return static_cast<std::uint64_t>(v.size()) * sizeof(T) * 8;
    }

}
