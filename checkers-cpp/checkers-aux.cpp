#include "checkers.hpp"

using namespace std;

void checkers::print_board() {
    cerr << "BOARD: " << endl;
    for (const auto& s : board) cerr << s << endl;
}

void checkers::print_pos() {
    cerr << "My positions: " << endl;
    for (const auto& pr : my_pos)
        fprintf(stderr, "%d %d, ", pr.first, pr.second);
    cerr << endl;
    cerr << "Rival positions: " << endl;
    for (const auto& pr : rival_pos)
        fprintf(stderr, "%d %d, ", pr.first, pr.second);
    cerr << endl;
}

vector<POINT> checkers::exist_capturing_handling(const POINT& pr,
                                                 const vector<POINT>& move_dir,
                                                 int sz, char rival) {
    vector<POINT> cap_ret;
    for (int i = 0; i < sz; i++) {
        POINT next = pr + move_dir[i];
        POINT next_next = next + move_dir[i];

        if (!is_inboundary(next_next)) continue;
        if ((getvalue(next) == rival || getvalue(next) == toupper(rival)) &&
            getvalue(next_next) == BLANK) {
            // avail_cap.insert(pr);
            cap_ret.push_back(next);
        }
    }

    return cap_ret;
}