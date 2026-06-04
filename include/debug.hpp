#pragma once

#include <bits/stdc++.h>

namespace debug {
    void printBits(std::uint64_t n) {
        std::print("bits: ");
        for (std::int64_t i = 63; i >= 0; i--) {

            std::uint64_t p = (n & (1ULL << i)) ? 1 : 0;
            std::print("{}", p);
        }
        std::println();
    }

    void printBitsString(std::uint64_t arr[], std::int64_t count) {
        std::print("bits 0-{}: ", count-1);
        for (std::int64_t i = 0; i < count; i++) {
            for (std::int64_t j = 63; j >= 0; j--) {
                std::uint64_t p = (arr[i] & (1ULL << j)) ? 1 : 0;
                std::print("{}", p);
            }
        }
        std::println();
    }

    void printGaps(std::vector<std::int64_t>& v, std::int64_t count) {
        for (std::int64_t i = 0; i < count; i++) {
            std::println("{}: {}", i+1, v[i+1]-v[i]);
        }
    }
}