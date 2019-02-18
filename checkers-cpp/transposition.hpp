#ifndef TRANSPOSITION_TABLE_H
#define TRANSPOSITION_TABLE_H

// transposition table

#include <utility>
#include <vector>

// when reserved memory for hash_map is not huge enough, this hash performs
// much much better than Zobrish hashing
struct VST_HASH {
    inline std::size_t operator()(const std::vector<std::string>& vst) const {
        size_t h = 0;
        for (const auto& str : vst) h ^= std::hash<std::string>()(str);
        return h;
    }
};

struct trans_table {
    using POINT = std::pair<int, int>;
    int searched_depth;
    std::vector<POINT> best_move;
    int value;
    trans_table(int _sd, std::vector<POINT>& _bm, int _val)
        : searched_depth(_sd), best_move(move(_bm)), value(_val) {}
};

#endif