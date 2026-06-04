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
                std::uint64_t diff_block_word_size; // block_size - word_size
                std::uint64_t mask_left; //  11100000 La cantidad de '1' es word_size
                std::uint64_t mask_right; // 00000111 La cantidad de '1' es word_size
            } gap;

            struct {
                T* array; // Arreglo
                T* begin; // Comienzo del arreglo
                T* end;    // Fin del arreglo
                std::uint64_t size; // Número de celdas
                std::uint64_t jump_length; // Tamaño del salto
            } sample;
            
            GapArray(std::vector<T>& v, std::uint64_t sample_jump_length) {
        
                // Encontrar el máximo valor del gap coding
                
                std::uint64_t max_T = 0;
                for (std::uint64_t i = 0; i < v.size() - 1; i++) {
                    // Como el vector está en orden no-decreciente la diferencia siempre será un número natural
                    // incluyendo el 0
                    std::int64_t cmp = (v[i+1] - v[i]);

                    if (max_T < cmp) {
                        std::cout << "idx: " << i << "max: " << max_T << endl;
                        max_T = cmp;
                    }
                }

                std::uint64_t max = static_cast<std::uint64_t>(max_T);
                /*
                typename std::vector<T>::iterator it = v.begin();

                while (it+1 != v.end()) {
                    // Como el vector está en orden no-decreciente la diferencia siempre será un número natural
                    // incluyendo el 0
                    std::uint64_t cmp = static_cast<std::uint64_t> (*(it+1) - *(it));
                    if (max < cmp)
                        max = cmp;
                    it++;
                }*/
            
                // Determinar número de bits necesarios para cada celda del vector a almacenar
                gap.word_size = WORD_SIZE_BITS;
                std::uint64_t mask = 0;
                while ((max & mask) == 0) {
                    mask |=  1ULL << gap.word_size;
                    gap.word_size--;
                }
                gap.word_size++;
                
                cout << "max: " << max << endl;
                cout << "gap word size: " << gap.word_size << endl;

                // Preparar el sample
                sample.size = v.size() / sample_jump_length + 1;
                sample.array = new T[sample.size];
                sample.begin = &sample.array[0];
                sample.end = &sample.array[sample.size];
                sample.jump_length = sample_jump_length;

                // Preparar el Gap Array para almacenar el vector compactamente
                gap.block_size = WORD_SIZE_BITS;
                gap.size = v.size();
                gap.physical_size = (std::uint64_t) std::ceil((gap.word_size * gap.size) / gap.block_size);
                gap.array = new std::uint64_t[gap.physical_size];
                gap.begin = &gap.array[0];
                gap.end = &gap.array[gap.physical_size];
                gap.mask_left = ~(~0 >> gap.word_size);
                gap.mask_right = ~0 >> (gap.block_size - gap.word_size);
                gap.diff_block_word_size = gap.block_size - gap.word_size;

                for (std::uint64_t* p = gap.begin; p != gap.end; p++) {
                    *p = 0;
                }

                std::uint64_t* gap_pointer = gap.begin;
                T* sample_pointer = sample.begin;

                *sample_pointer = *v.begin();
                sample_pointer++;

                std::int64_t shift_amount = gap.block_size - gap.word_size;
                std::cout << "real shift amount: " << shift_amount << endl;
                std::uint64_t difference;

                for (std::uint64_t i = 0; i < v.size() - 1; i++) {
                    difference = (std::uint64_t) (v[i+1] - v[i]);
                    shift_amount -= gap.word_size;

                    if (shift_amount >= 0) {
                        *gap_pointer |= difference << shift_amount;
                    }
                    else {
                        *gap_pointer |= difference >> (-1 * shift_amount);
                        gap_pointer++;
                        shift_amount += gap.block_size;
                        *gap_pointer |= difference << shift_amount;
                    }

                    if (i % (sample.jump_length + 1) == 0) {
                        *sample_pointer = v[i];
                        sample_pointer++;
                    }
                }

            }

            ~GapArray() {
                // Destructor
                delete [] gap.array;
                delete [] sample.array;
            }

            T get(std::uint64_t index) {
                T value = sample.array[index/(sample.jump_length + 1)];
                
                std::uint64_t sample_index_in_gap = (index/(sample.jump_length + 1)) * (sample.jump_length + 1);
                std::uint64_t sample_index_bits = sample_index_in_gap * gap.word_size;
                
                std::uint64_t gap_index = sample_index_bits / gap.block_size;
                std::uint64_t* gap_pointer = &gap.array[gap_index];
                std::int64_t shift_amount = gap.block_size - sample_index_bits + (gap_index * gap.block_size);

                
                for (std::uint64_t i = 0; i < index - sample_index_in_gap; i++) {
                    shift_amount -= gap.word_size;
                    if (shift_amount >= 0) {
                        value += (*gap_pointer & (gap.mask_right << shift_amount)) >> shift_amount;
                    }
                    else {
                        value += (*gap_pointer & (gap.mask_right >> -shift_amount)) << -shift_amount;
                        gap_pointer++;
                        shift_amount += gap.block_size;
                        value += (*gap_pointer & (gap.mask_right << shift_amount)) >> shift_amount;
                        std::uint64_t calc = gap.block_size - shift_amount;
                    }
                }
                return value;

                /*
                std::uint64_t bits = index * gap.word_size;
                std::uint64_t gap_block_start_bit = (bits / gap.block_size)*gap_block_size;
                std::uint64_t gap_pointer  = gap.array[bits / gap.block_size];
                std::uint64_t mov = bits % gap.block_size;
                std::uint64_t sum = 0;

                for (int i = 0; i < mov; i++) {
                    std:: cout << "\nIM INSIDE YOUR HOUSE \n";
                    sum += gap.word_size;
                    value += static_cast<std::uint64_t>((gap.array[p1] & (gap.mask_left >> sum)) >> (gap.block_size - sum));
                }
                return value;
                */
            }

    };

    /*
    template<typename T>
    
    GapArray<T> build(std::vector<T> v, int64_t sample_jump_length) {

        return GapArray<T>(v, word_size);

        // Adaptar

        if (32 < word_size && word_size <= 64) {
            return GapArray<std::uint64_t>(v, word_size);
        }
        else if (16 < word_size && word_size <= 32) {
            return GapArray<uint32_t>(v, word_size);
        } 
        else if (8 < word_size && word_size <= 16) {
            return GapArray<uint16_t>(v, word_size);
        }
        else {
            return GapArray<uint8_t>(v, word_size);
        }
        

        println("Número de bits por celda requeridos para representar el vector: {}b",
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