#pragma once

#include <bits/stdc++.h>
#include "gap_coding.hpp"

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

    void compareGaps(std::vector<std::int64_t>& v, gap_coding::GapArray<std::int64_t>& gc) {
        std::uint64_t i;
        for (i = 0; i < v.size()-1; i++) {
            if (static_cast<std::uint64_t>(v[i+1] - v[i]) != gc.get_gap(i+1))
                break; 
        }
        std::print("compareGaps: ");
        if (i == v.size()-1)
            std::print("Gaps are equal");
        else
            std::print("Gaps are not equal: index: ", i+1);
        std::println();
    }

    void compareWithGapCoding(std::vector<std::int64_t>& v, gap_coding::GapArray<std::int64_t>& gc) {
        std::uint64_t i;
        for (i = 0; i < v.size(); i++) {
            if(v[i] != gc.get(i))
                break;
        }
        std::print("compareWithGapCoding: ");
        if (i == v.size())
            std::print("Values are equal");
        else
            std::print("Values are not equal: index: {}", i);
        std::println();
    }
}