// probability based ship hit

#include "battleship.hpp"

using namespace std;

vector<vector<int>> battleship::probability_estimate(
    const vector<string>& board, int max_est_size) {
    vector<vector<int>> ret(board_size, vector<int>(board_size, 0));

    // horizontal loop
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j <= board[i].size() - max_est_size; j++) {
            bool can_place_here = true;
            for (int j1 = 0; j1 < max_est_size; j1++) {
                if (board[i][j + j1] != '-') can_place_here = false;
            }
            if (can_place_here) {
                for (int j1 = 0; j1 < max_est_size; j1++) {
                    ret[i][j + j1]++;
                }
            }
        }
    }

    // vertical loop
    for (int i = 0; i <= board.size() - max_est_size; i++) {
        for (int j = 0; j < board[i].size(); j++) {
            bool can_place_here = true;
            for (int j1 = 0; j1 < max_est_size; j1++) {
                if (board[i + j1][j] != '-') can_place_here = false;
            }
            if (can_place_here) {
                for (int j1 = 0; j1 < max_est_size; j1++) {
                    ret[i + j1][j]++;
                }
            }
        }
    }

    return ret;
}

point battleship::hit_ship_probability_based(const vector<string>& board) {
    int pboard_est = 5;
    while (pboard_est > 1) {
        vector<vector<int>> pboard = probability_estimate(board, pboard_est);

        /*
        for (const auto& i : pboard) {
            for (const auto& j : i) cerr << j << " ";
            cerr << endl;
        }
        */

        int maxp = 0;
        point cur = {0, 0};

        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                if (pboard[i][j] > maxp) {
                    maxp = pboard[i][j];
                    cur = {i, j};
                }
            }
        }

        if (maxp != 0)
            return cur;
        else
            pboard_est--;
    }
    return hit_ship_fully_random(board);
}