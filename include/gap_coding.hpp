#pragma once

#include <bits/stdc++.h>

#define WORD_SIZE_BITS 64 
#define STD_UINT8_T_BITS 8

namespace gap_coding {
    template<typename T>
    class GapArray {
        public:
            struct {
                std::uint64_t* array; // Arreglo
                std::uint64_t* begin; // Comienzo del arreglo
                std::uint64_t* end;   // Fin del arreglo
                std::uint64_t word_size; // Tamaño virtual de las celdas
                std::uint64_t size; // Número de celdas en bits virtuales
                std::uint64_t physical_size; // Número de celdas de 64 bits
                std::uint64_t block_size; // Tamaño fisico de cada celda (bloque) (64 bits)
                std::uint64_t mask_left;
            } gap;

            struct {
                T* array; // Arreglo
                T* begin; // Comienzo del arreglo
                T* end;    // Fin del arreglo
                std::uint64_t size; // Número de celdas
                std::uint64_t jump_length; // Tamaño del salto
            } sample;
            
            GapArray(std::vector<T> v, std::uint64_t sample_jump_length) {
        
                // Encontrar el máximo valor del gap coding
                T* p = v.begin();
                std::uint64_t max = *p;
                while (++p != v.end()) {
                    /*  Como el vector está en orden no-decreciente la diferencia siempre será un número natural
                        incluyendo el 0 */
                    std::uint64_t cmp = (std::int64_t) (*(p+1) - *(p));
                    if (max < cmp)
                        max = cmp;
                }
            
                // Determinar número de bits necesarios para cada celda del vector a almacenar
                std::uint64_t word_size = WORD_SIZE_BITS;
                std::uint64_t mask = 0;
                while (max & mask)
                    mask +=  1 << --word_size;
                word_size++;

                // Preparar el sample
                sample.size = v.size() / sample_jump_length + 1;
                sample.array = new T[sample.size];
                sample.begin = &sample.array[0];
                sample.end = &sample.array[sample.size];
                sample.jump_length = sample_jump_length;

                // Preparar el Gap Array para almacenar el vector compactamente
                gap.block_size = sizeof(std::uint64_t)*STD_UINT8_T_BITS;
                gap.word_size = word_size;
                sample.jump_length = sample_jump_length;
                gap.size = v.size();
                gap.physical_size = (std::uint64_t) std::ceil((gap.word_size * gap.size) / gap.block_size);
                gap.array = new std::uint64_t[gap.physical_size];
                gap.begin = &gap.array[0];
                gap.end = &gap.array[gap.physical_size];
                gap.mask_left = ~(~0 >> gap.word_size);

                std::uint64_t* gap_pointer = gap.begin;
                T* sample_pointer = sample.begin;

                *sample_pointer = *v.begin();
                sample_pointer++;
                p++;

                std::uint64_t i = 0;
                std::int64_t shift_amount = block_size;
                std::uint64_t value;

                for (std::uint64_t i = 0; i < v.size() - 1; i++) {
                    value = (std::uint64_t) v[i+1] - v[i];
                    shift_amount -= word_size;

                    if (shift_amount >= 0) {
                        *gap_pointer += value << shift_amount;
                    }
                    else {
                        *gap_pointer += value >> -shift_amount;
                        gap_pointer++;
                        gap_pointer += value << shift_amount;
                    }

                    if (i % (sample.jump_length + 1) == 0) {
                        *sample_pointer = v[i];
                        sample_pointer++;
                    }
                }
                
                /*
                while (p != v.end()) {
                    // Almacenar elementos shifteando los bits a sus posiciones respectivas
                    value = (std::uint64_t) (*p - *(p-1));
                    shift_amount -= word_size;
                    
                    if (shift_amount >= 0) {
                        *gp_p += value << shift_amount;
                    }
                    else {
                        *gp_p += value >> -shift_amount;
                        if (shift_amount != 0) {
                            shift_amount += block_size;
                            *(gp_p + 1) += value << shift_amount;
                        }
                        gp_p++;
                    }

                    p++;
                } */

            }

            ~GapArray() {
                // Destructor
                delete [] gap.array;
                delete [] sample.array;
            }

            T get(std::uint64_t index) {
                T value = sample.array[index/(sample.jump_length + 1)];
                std::uint64_t p0 = index * word_size;
                std::uint64_t p1 = p0 / block_size;
                std::uint64_t p2 = p0 % block_size;
                std::uint64_t sum = 0;
                while (sum < p2) {
                    gap.mask_left >> p2;
                    sum += gap.word_size;
                    value += (gap.array[p1] & (gap.mask_left >> sum)) >> (gap.block_size - gap.word_size);
                }
            }

    };

    /*
    template<typename T>
    
    GapArray<T> build(std::vector<T> v, std::int64_t sample_jump_length) {

        return GapArray<T>(v, word_size);

        // Adaptar

        if (32 < word_size && word_size <= 64) {
            return GapArray<std::uint64_t>(v, word_size);
        }
        else if (16 < word_size && word_size <= 32) {
            return GapArray<std::uint32_t>(v, word_size);
        } 
        else if (8 < word_size && word_size <= 16) {
            return GapArray<std::uint16_t>(v, word_size);
        }
        else {
            return GapArray<std::uint8_t>(v, word_size);
        }
        

        std::println("Número de bits por celda requeridos para representar el vector: {}b",
             word_size)

        std::vector<std::uint64_t> initial_gap;
        initial_gap.reserve(v.size());
        T* p = v.begin();
        initial_gap.push_back(*p);
        ++p;

        while (p != v.end()) {
            initial_gap.push_back(*(++p) - *p);
        }
    }
    */

}