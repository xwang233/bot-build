#include "battleship.hpp"

using namespace std;

point battleship::hit_ship_adjacent_bfs(const vector<string>& board,
                                        point start) {
    queue<point> que;
    que.push(start);
    while (!que.empty()) {
        point cur = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            point next = cur + dir_vec_map[i];
            if (is_inboundary(next)) {
                char c = getpoint(board, next);

                if (c == 'h') que.push(next);
                if (c == '-') return next;
            }
        }
    }

    // bfs everything but not find anything? impossible
    return hit_ship_fully_random(board);
}

point battleship::hit_ship_adjacent_advanced(const vector<string>& board,
                                             point start) {
    point nexth0 = start + dir_vec_map[0];
    point nexth2 = start + dir_vec_map[2];

    point nextv1 = start + dir_vec_map[1];
    point nextv3 = start + dir_vec_map[3];

    bool check_h = false;
    if ((is_inboundary(nexth0) && getpoint(board, nexth0) == 'h') ||
        (is_inboundary(nexth2) && getpoint(board, nexth2) == 'h')) {
        check_h = true;
    }

    bool check_v = false;
    if ((is_inboundary(nextv1) && getpoint(board, nextv1) == 'h') ||
        (is_inboundary(nextv3) && getpoint(board, nextv3) == 'h')) {
        check_v = true;
    }

    if (check_h) {
        while (is_inboundary(nexth0)) {
            if (getpoint(board, nexth0) == 'h') {
                nexth0 = nexth0 + dir_vec_map[0];
                continue;
            }
            if (getpoint(board, nexth0) == '-') return nexth0;

            break;
        }

        while (is_inboundary(nexth2)) {
            if (getpoint(board, nexth2) == 'h') {
                nexth2 = nexth2 + dir_vec_map[2];
                continue;
            }
            if (getpoint(board, nexth2) == '-') return nexth2;

            break;
        }
    }

    if (check_v) {
        while (is_inboundary(nextv1)) {
            if (getpoint(board, nextv1) == 'h') {
                nextv1 = nextv1 + dir_vec_map[1];
                continue;
            }
            if (getpoint(board, nextv1) == '-') return nextv1;

            break;
        }

        while (is_inboundary(nextv3)) {
            if (getpoint(board, nextv3) == 'h') {
                nextv3 = nextv3 + dir_vec_map[3];
                continue;
            }
            if (getpoint(board, nextv3) == '-') return nextv3;

            break;
        }
    }

    return hit_ship_adjacent_bfs(board, start);
}

point battleship::hit_ship_adjacent_random(const vector<string>& board) {
    bool hit_exist = false;
    point hitat;

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            char c = board[i][j];
            if (c == 'h') {
                hit_exist = true;
                hitat = {i, j};
                goto forbreak;
            }
        }
    }
forbreak:

    if (hit_exist)
        //return hit_ship_adjacent_bfs(board, hitat);
        return hit_ship_adjacent_advanced(board, hitat); 
    else
        //return hit_ship_fully_random(board);
        return hit_ship_probability_based(board); 
}

point battleship::hit_ship_fully_random(const vector<string>& board) {
    point ret = {randx(), randx()};
    while (getpoint(board, ret) != '-') {
        ret = {randx(), randx()};
    }
    return ret;
}
