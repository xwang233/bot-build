#include "checkers.hpp"

using namespace std;

int checkers::next_move() {
    if (exist_capturing()) {
        next_move_cap();
    } else {
        next_move_noncap();
    }

    return 0;
};

int checkers::next_move_cap() {
    POINT cur = *avail_cap.begin();
    POINT orig = cur;
    vector<POINT> moves;

    while (next_move_one(cur, moves))
        ;
    printf("%lu\n", moves.size());
    printf("%d %d\n", orig.first, orig.second);
    for (const auto& pt : moves) {
        printf("%d %d\n", pt.first, pt.second);
    }

    return 0;
}

int checkers::next_move_one(POINT& pt, vector<POINT>& moves) {
    vector<POINT> cap;
    if (getvalue(pt) == WHOSTURN) {
        cap = exist_capturing_handling(pt, forward_dir_vec, 2);
    } else if (getvalue(pt) == towupper(WHOSTURN)) {
        cap = exist_capturing_handling(pt, all_dir_vec, 4);
    } else {
        return 0;
    }

    if (cap.empty()) return 0;

    POINT next = *cap.begin();
    POINT next_next = next + next - pt;
    if ((next_next.first == 0 && WHOSTURN == 'w') ||
        (next_next.first == board_size - 1 && WHOSTURN == 'b')) {
        setvalue(next_next) = toupper(WHOSTURN);
    } else {
        setvalue(next_next) = getvalue(pt);
    }
    setvalue(pt) = BLANK;
    setvalue(next) = BLANK;

    moves.push_back(next_next);
    pt = next_next;

    return 1;
}

int checkers::next_move_noncap() {
    POINT pt = *avail_move.begin();
    vector<POINT> cap;
    if (getvalue(pt) == WHOSTURN) {
        cap = next_move_handling(pt, forward_dir_vec, 2);
    } else if (getvalue(pt) == towupper(WHOSTURN)) {
        cap = next_move_handling(pt, all_dir_vec, 4);
    } else {
        return 0;
    }

    POINT& next = cap[0];
    printf("1\n%d %d\n%d %d\n", pt.first, pt.second, next.first, next.second);

    return 0;
}