#pragma once

// Caso 1: (Linea Base).
// El arreglo ordenado se almacena directamente como std::vector<T>.
// La busqueda usa std::binary_search / std::lower_bound de la biblioteca estandar.
//
// Construccion: sort(v.begin(), v.end())   -- O(n log n)
// Busqueda: lower_bound(v.begin(), v.end(), x)  -- O(log n)
//
// Las funciones de medicion de N busquedas (trueRandom y selectRandom para vector)
// estan en binary_search.hpp.

#include "binary_search.hpp"

namespace caso1 {

    // Ordena el vector en su lugar. Debe llamarse antes de buscar.
    template<typename T>
    void construir(std::vector<T>& v) {
        std::sort(v.begin(), v.end());
    }

    // Busca x en el vector ordenado. Devuelve su posicion (0-indexed) o -1 si no esta.
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
