#ifndef XW_CHECKERS_H
#define XW_CHECKERS_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using POINT = std::pair<int, int>;
struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& pr) const {
        return std::hash<int>()(pr.first * 10 + pr.second);
    }
};

inline POINT operator+(POINT l, const POINT& r) {
    l.first += r.first;
    l.second += r.second;
    return l;
};

inline POINT operator*(POINT l, int r) {
    l.first *= r;
    l.second *= r;
    return l;
}

inline POINT operator-(POINT l, const POINT& r) {
    l.first -= r.first;
    l.second -= r.second;
    return l;
}

class checkers {
    using BOARD = std::vector<std::string>;

    char WHOSTURN;
    char RIVAL;
    const char BLANK = '_';
    BOARD board;
    int board_size;
    std::unordered_set<POINT, pair_hash> my_pos;
    std::unordered_set<POINT, pair_hash> rival_pos;
    std::unordered_set<POINT, pair_hash> avail_cap;
    std::unordered_set<POINT, pair_hash> avail_move;

    const POINT dir_vec[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    POINT forward_dir_vec[2];
    POINT all_dir_vec[4] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    bool is_inboundary(const POINT& pt) {
        return pt.first >= 0 && pt.first < board_size && pt.second >= 0 &&
               pt.second < board_size;
    }
    const char& getvalue(const POINT& pt) { return board[pt.first][pt.second]; }
    char& setvalue(const POINT& pt) { return board[pt.first][pt.second]; }

    int update_mypos(const std::string&);

    bool exist_capturing();
    std::vector<POINT> exist_capturing_handling(const POINT&, POINT*, int);
    int next_move();
    std::vector<POINT> next_move_handling(const POINT&, POINT*, int);

    int next_move_cap();
    int next_move_noncap();
    int next_move_one(POINT&, std::vector<POINT>&);

   public:
    int process(const std::string&);
    void print_board();
    void print_pos();
};

#endif