#pragma once

#include <bits/stdc++.h>

// Caso 3: compresion del arreglo de gaps con Shannon-Fano.
// Los gaps se guardan como codigos de largo variable, empaquetados bit a bit en un
// arreglo de uint64. El sample (igual que el Caso 2) evita tener que decodificar
// desde el principio en cada busqueda.

namespace caso3 {

    template<typename T>
    class ShannonFano {
        public:
            // Un codigo de largo variable: los bits van en 'word' (pegados a la derecha, el primero es el de mas peso) 
            // 'length' dice cuantos valen.
            struct Codigo {
                std::uint64_t word;
                std::uint32_t length;
            };

            std::vector<std::uint64_t> bits; // el arreglo comprimido, como mapa de bits
            std::uint64_t total_bits;      // cuantos bits llevamos escritos

            std::vector<T> muestra_vals;          // valores del sample
            std::vector<std::uint64_t> muestra_bits; // en que bit arranca el gap que sigue a cada muestra

            // Para decodificar: de (length, word) saca el gap. Como ningun codigo es
            // prefijo de otro, se puede ir leyendo bit a bit sin confundirse.
            std::map<std::pair<std::uint32_t, std::uint64_t>, T> decodificador;

            std::uint64_t saltos;
            std::uint64_t total_elementos;

            ShannonFano(std::vector<T> valores, std::uint64_t saltos) {
                this->saltos = saltos;
                this->total_elementos = valores.size();
                this->total_bits = 0;

                std::sort(valores.begin(), valores.end());

                // gaps
                std::vector<T> gaps;
                for (std::uint64_t i = 1; i < valores.size(); i++) {
                    gaps.push_back(valores[i] - valores[i - 1]);
                }

                // cuantas veces aparece cada gap
                std::map<T, std::uint64_t> frecuencias;
                for (T g : gaps) {
                    frecuencias[g]++;
                }

                std::map<T, Codigo> codigos = shannon_fano_codigos(frecuencias);

                // tabla inversa para poder decodificar despues
                for (auto& par : codigos) {
                    decodificador[{par.second.length, par.second.word}] = par.first;
                }

                // recorremos los gaps escribiendolos, y cada 'saltos' guardamos una muestra
                muestra_vals.push_back(valores[0]);
                muestra_bits.push_back(0);

                for (std::uint64_t i = 0; i < gaps.size(); i++) {
                    Codigo c = codigos[gaps[i]];
                    escribir_bits(c.word, c.length);

                    if ((i + 1) % saltos == 0) {
                        muestra_vals.push_back(valores[i + 1]);
                        muestra_bits.push_back(total_bits);
                    }
                }
            }

            // Busca x. Devuelve su posicion en el arreglo ordenado, o -1 si no esta.
            std::int64_t buscar(T x) {
                std::int64_t i = encontrar_bloque(x);
                if (i < 0) {
                    return -1;
                }

                T val_actual = muestra_vals[i];
                std::uint64_t pos = (std::uint64_t) i * saltos; // la muestra i es el elemento i*saltos
                std::uint64_t bit_pos = muestra_bits[i];

                if (val_actual == x) {
                    return (std::int64_t) pos;
                }

                // desde la muestra vamos sumando gaps hasta llegar a x o pasarnos
                while (bit_pos < total_bits) {
                    std::uint64_t word = 0;
                    std::uint32_t length = 0;
                    bool encontrado = false;

                    // leemos bits hasta que (length, word) sea un codigo conocido
                    while (bit_pos < total_bits) {
                        word = (word << 1) | leer_bit(bit_pos);
                        length++;
                        bit_pos++;
                        if (decodificador.count({length, word})) {
                            encontrado = true;
                            break;
                        }
                    }

                    if (!encontrado) {
                        break;
                    }

                    val_actual += decodificador[{length, word}];
                    pos++;

                    if (val_actual == x) {
                        return (std::int64_t) pos;
                    }
                    if (val_actual > x) {
                        return -1;
                    }
                }

                return -1;
            }

            // por si solo interesa saber si esta o no
            bool esta_o_no(T x) {
                return buscar(x) >= 0;
            }

            // cuanto ocupa todo en bits: el arreglo comprimido mas el sample
            std::uint64_t espacio_bits() {
                std::uint64_t bits_comprimido = bits.size() * 64;
                std::uint64_t bits_sample = muestra_vals.size() * (sizeof(T) * 8) + muestra_bits.size() * 64;
                return bits_comprimido + bits_sample;
            }

        private:
            // agrega 'length' bits de 'word' al final del mapa (primero el de mas peso)
            void escribir_bits(std::uint64_t word, std::uint32_t length) {
                for (std::int32_t b = length - 1; b >= 0; b--) {
                    std::uint64_t bit = (word >> b) & 1ULL;
                    std::uint64_t idx = total_bits / 64;
                    std::uint64_t off = total_bits % 64;
                    if (idx >= bits.size()) {
                        bits.push_back(0);
                    }
                    if (bit) {
                        bits[idx] |= (1ULL << (63 - off));
                    }
                    total_bits++;
                }
            }

            std::uint64_t leer_bit(std::uint64_t pos) {
                std::uint64_t idx = pos / 64;
                std::uint64_t off = pos % 64;
                return (bits[idx] >> (63 - off)) & 1ULL;
            }

            // busqueda binaria en el sample: la mayor muestra <= x (o -1 si x es menor que todo)
            std::int64_t encontrar_bloque(T x) {
                std::int64_t l = 0;
                std::int64_t r = (std::int64_t) muestra_vals.size() - 1;
                while (l <= r) {
                    std::int64_t m = (l + r) / 2;
                    if (muestra_vals[m] <= x) {
                        l = m + 1;
                    } else {
                        r = m - 1;
                    }
                }
                return r;
            }

            std::map<T, Codigo> shannon_fano_codigos(std::map<T, std::uint64_t>& frecuencias) {
                std::vector<std::pair<T, std::uint64_t>> pares(frecuencias.begin(), frecuencias.end());

                // ordenamos por frecuencia, de mayor a menor. El primer sort por símbolo
                // es solo para que los empates de frecuencia queden siempre en el mismo orden.
                std::sort(pares.begin(), pares.end(),
                    [](const std::pair<T, std::uint64_t>& a, const std::pair<T, std::uint64_t>& b) {
                        return a.first < b.first;
                    });
                std::stable_sort(pares.begin(), pares.end(),
                    [](const std::pair<T, std::uint64_t>& a, const std::pair<T, std::uint64_t>& b) {
                        return a.second > b.second;
                    });

                std::map<T, Codigo> codigos;
                if (!pares.empty()) {
                    construir_codigos(pares, codigos, 0, (std::int64_t) pares.size() - 1, 0, 0);
                }
                return codigos;
            }

            // parte [lo, hi] en dos mitades de frecuencia parecida y baja recursivamente.
            // word/length es el codigo que llevamos acumulado.
            void construir_codigos(std::vector<std::pair<T, std::uint64_t>>& pares,
                                   std::map<T, Codigo>& codigos,
                                   std::int64_t lo, std::int64_t hi,
                                   std::uint64_t word, std::uint32_t length) {
                if (lo > hi) {
                    return;
                }
                if (lo == hi) {
                    // hoja. El unico caso raro es que haya un solo símbolo en todo: le damos "0"
                    if (length == 0) {
                        word = 0;
                        length = 1;
                    }
                    codigos[pares[lo].first] = {word, length};
                    return;
                }

                long double total = 0;
                for (std::int64_t i = lo; i <= hi; i++) {
                    total += pares[i].second;
                }
                long double mitad = total / 2;

                // cortamos donde las dos mitades queden con frecuencias lo más parejas posible
                long double suma = 0;
                long double mejor_diff = std::numeric_limits<long double>::max();
                std::int64_t corte = lo;
                for (std::int64_t i = lo; i < hi; i++) {
                    suma += pares[i].second;
                    long double diff = std::fabsl(suma - mitad);
                    if (diff < mejor_diff) {
                        mejor_diff = diff;
                        corte = i;
                    }
                }

                // la izquierda (mayor frecuencia) lleva un 1, la derecha un 0
                construir_codigos(pares, codigos, lo, corte, (word << 1) | 1, length + 1);
                construir_codigos(pares, codigos, corte + 1, hi, (word << 1) | 0, length + 1);
            }
    };

}
