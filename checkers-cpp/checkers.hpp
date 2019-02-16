#ifndef XW_CHECKERS_H
#define XW_CHECKERS_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "zobrist_hashing.hpp"

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

inline POINT operator/(POINT l, int r) {
    l.first /= r;
    l.second /= r;
    return l;
}

class checkers {
   public:
    using BOARD = std::vector<std::string>;

    char WHOSTURN;
    char RIVAL;
    const char BLANK = '_';
    BOARD board;
    int board_size;
    std::unordered_set<POINT, pair_hash> my_pos;
    std::unordered_set<POINT, pair_hash> rival_pos;

    std::unordered_map<BOARD, std::pair<std::vector<std::vector<POINT>>, int>,
                       Zobrist_HASH>
        avail_move_cache;

    const POINT dir_vec[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    // POINT forward_dir_vec[2];
    const std::vector<POINT> all_dir_vec = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    std::unordered_map<char, std::vector<POINT>> forward_dir_vec;

    bool is_inboundary(const POINT& pt) {
        return pt.first >= 0 && pt.first < board_size && pt.second >= 0 &&
               pt.second < board_size;
    }
    const char& getvalue(const POINT& pt) { return board[pt.first][pt.second]; }
    char& setvalue(const POINT& pt) { return board[pt.first][pt.second]; }

    std::vector<POINT> exist_capturing_handling(const POINT&,
                                                const std::vector<POINT>&, int,
                                                char);
    int next_move();

    template <int (checkers::*)()>
    std::pair<std::vector<POINT>, int> minimax(int, char, bool, int, int); 
    int eval(char);
    int eval();
    int eval2();

    const int CAP = 0;
    const int MOVE = 1;
    std::pair<std::vector<std::vector<POINT>>, int> get_avail_move(char);
    void get_next_cap(const POINT&, std::vector<std::vector<POINT>>&,
                      std::vector<POINT>&, char);
    void get_next_nocap(const POINT&, std::vector<std::vector<POINT>>&, char);

   public:
    checkers() {
        forward_dir_vec['w'] = {{-1, 1}, {-1, -1}};
        forward_dir_vec['b'] = {{1, 1}, {1, -1}};
    }
    int process(const std::string&);
    void print_board();
    void print_pos();
    const BOARD& getboard() { return board; }
    void setboard(const BOARD& _board) {
        board = _board;
        board_size = board.size();
    }
    void setboard(const std::string& str) {
        board_size = (int)sqrt(str.size());
        if (board_size * board_size != str.size()) {
            std::cerr << "STR size wrong! default initialized!" << std::endl;
            BOARD _board = {"_b_b_b_b", "b_b_b_b_", "_b_b_b_b", "________",
                            "________", "w_w_w_w_", "_w_w_w_w", "w_w_w_w_"};
            setboard(_board);
            return;
        }
        board.clear();
        for (int i = 0; i < str.size(); i++) {
            if (i % board_size == 0) board.push_back("");
            board.back().push_back(str[i]);
        }
    }
    void setplayer(char c) {
        WHOSTURN = c;
        RIVAL = 'w' + 'b' - c;
    }
    char getplayer() { return WHOSTURN; }

   public:
    std::vector<POINT> next_move_handling();
    std::vector<POINT> random_move();
    // void move_from_vp(const std::vector<POINT>&, char);
    std::unordered_map<POINT, char, pair_hash> move_from_vp(
        const std::vector<POINT>&, char);
};

#endif