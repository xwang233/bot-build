#ifndef ZOBRIST_HASH_H
#define ZOBRIST_HASH_H

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

struct Zobrist_HASH {
    //inline static std::vector<std::vector<size_t>> zobrist_table;
    inline static size_t zobrist_table[64][4]; 
    inline size_t operator()(const std::vector<std::string>& vst) const {
        /*
        assert(!zobrist_table.empty() &&
               "You probably forgot to initialize the zobrist_table. Use \
Zobrist_HASH::init_table(); ");
        */
        size_t h = 0;
        int i = 0;
        for (const auto& str : vst) {
            for (const auto& c : str) {
                // if (!value.count(c)) continue;
                if (c == '_') continue;

                size_t idx;
                switch (c) {
                    case ('w'): idx = 0; break;
                    case ('W'): idx = 1; break;
                    case ('b'): idx = 2; break;
                    case ('B'): idx = 3; break;
                }
                h ^= zobrist_table[i][idx];
                i++;
            }
        }
        return h;
    }

    static void init_table(int board_size, int piece_nums) {
        // zobrist_table.clear();
        for (int i = 0; i < board_size; i++) {
            // zobrist_table.push_back({});
            for (int j = 0; j < piece_nums; j++) {
                //zobrist_table.back().push_back( rand() % std::numeric_limits<size_t>::max());
                zobrist_table[i][j] = rand() % std::numeric_limits<size_t>::max(); 
            }
        }
    }

    static void print_table() {
        for (const auto& vs : zobrist_table) {
            for (const auto& s : vs) std::cout << s << std::endl;
        }
    }
};

#endif