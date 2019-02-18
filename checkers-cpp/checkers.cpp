#include "checkers.hpp"

using namespace std;

int checkers::process(const string& str) {
    if (str.size() == 1) {
        if (str[0] == 'w') {
            WHOSTURN = 'w';
            RIVAL = 'b';
            // forward_dir_vec[0] = {-1, 1};
            // forward_dir_vec[1] = {-1, -1};
        } else if (str[0] == 'b') {
            WHOSTURN = 'b';
            RIVAL = 'w';
            // forward_dir_vec[0] = {1, 1};
            // forward_dir_vec[1] = {1, -1};
        } else
            board_size = str[0] - '0';

        return 0;
    } else {
        board.push_back(str);
    }

    if (board.size() == board_size) {
        next_move();
        return 1;
    } else {
        return 0;
    }
}

int checkers::next_move() {
    auto rets = minimax<&checkers::eval2>(0, WHOSTURN, true, -1000, 1000);
    auto ret = rets.first;
    printf("%lu\n", ret.size() - 1);
    for (const auto& pt : ret) {
        printf("%d %d\n", pt.first, pt.second);
    }
    cerr << rets.second << endl;
    return 0;
}

vector<POINT> checkers::next_move_handling() {
    auto rets = minimax<&checkers::eval2>(0, WHOSTURN, true, -1000, 1000);
    // cerr << rets.second << endl;
    return rets.first;
}

void checkers::setboard(const BOARD& _board) {
    board = _board;
    board_size = board.size();
}
void checkers::setboard(const std::string& str) {
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