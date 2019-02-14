#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pair_as_point.hpp"

class battleship {
   private:
    bool initiated = false;
    const int board_size = 10;

    std::vector<point> dir_vec_map = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    std::vector<std::string> cur_board;

    int randx() { return rand() % board_size; }

    bool is_inboundary(point& pt) {
        if (pt.first >= 0 && pt.first < board_size && pt.second >= 0 &&
            pt.second < board_size)
            return true;
        else
            return false;
    }

    char getpoint(const std::vector<std::string>& board, point pt) {
        return board[pt.first][pt.second];
    }

    char& setpoint(std::vector<std::string>& board, point pt) {
        return board[pt.first][pt.second];
    }

    // bs_init_ship.cpp
    std::string place_ship(std::vector<std::string>& board, int boat_size);
    std::string place_ship_size_one(std::vector<std::string>& board,
                                    bool iseven);
    std::vector<std::string> ship_init();

    // bs_hit_ship.cpp
    point hit_ship_adjacent_bfs(const std::vector<std::string>& board,
                                point start);
    point hit_ship_adjacent_advanced(const std::vector<std::string>& board,
                                     point start);
    point hit_ship_adjacent_random(const std::vector<std::string>& board);
    point hit_ship_fully_random(const std::vector<std::string>& board);

    // bs_hit_ship.1.cpp
    std::vector<std::vector<int>> probability_estimate(
        const std::vector<std::string>& board, int max_est_size);
    point hit_ship_probability_based(const std::vector<std::string>& board);

    // battleship.cpp
    int read_handle(std::string str);

   public:
    int process(std::string str);
};

#endif