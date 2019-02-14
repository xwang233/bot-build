#ifndef TTT_H
#define TTT_H

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

// tic-tac-toe
class ttt {
    int board_size = 4;
    std::string board;
    char whosturn;
    char rival;
    const char blank = '_';

    int next_move();
    bool is_tie();
    bool is_wining(char);
    std::pair<int, int> minimax(int, char, bool, int, int);
    std::unordered_set<int> check_avail_play();

   public:
    int process(const std::string&);
    void print_board();
};

#endif