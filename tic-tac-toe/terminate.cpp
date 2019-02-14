#include "ttt.hpp"

using namespace std;

bool ttt::is_wining(char c) {
    vector<bool> col(board_size, true);
    vector<bool> row(board_size, true);
    vector<bool> diag(2, true);

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            int idx = i * board_size + j;
            bool judge = (board[idx] == c);
            col[i] = col[i] && judge;
            row[j] = row[j] && judge;
            if (i == j) diag[0] = diag[0] && judge;
            if (i + j == board_size - 1) diag[1] = diag[1] && judge;
        }
    }

    if (diag[0] || diag[1]) {
        return true;
    }
    for (int i = 0; i < board_size; i++) {
        if (col[i] || row[i]) {
            return true;
        }
    }
    return false;
}

bool ttt::is_tie() {
    auto avail_play = check_avail_play();
    if (avail_play.empty()) return true;
    return false;
}