#include "checkers.hpp"

using namespace std;

int checkers::process(const string& str) {
    if (str.size() == 1) {
        if (str[0] == 'w') {
            WHOSTURN = 'w';
            RIVAL = 'b';
            forward_dir_vec[0] = {-1, 1};
            forward_dir_vec[1] = {-1, -1};
        } else if (str[0] == 'b') {
            WHOSTURN = 'b';
            RIVAL = 'w';
            forward_dir_vec[0] = {1, 1};
            forward_dir_vec[1] = {1, -1};
        } else
            board_size = str[0] - '0';

        return 0;
    } else {
        board.push_back(str);
        update_mypos(str);
    }

    if (board.size() == board_size) {
        next_move();
        return 1;
    } else {
        return 0;
    }
}

int checkers::update_mypos(const string& str) {
    int row = board.size() - 1;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == WHOSTURN || str[i] == toupper(WHOSTURN))
            my_pos.insert({row, i});
        else if (str[i] == RIVAL || str[i] == toupper(RIVAL))
            rival_pos.insert({row, i});
    }

    return 0;
}
