#include "checkers.hpp"

using namespace std;

void checkers::print_board() {
    cout << "BOARD: " << endl;
    for (const auto& s : board) cout << s << endl;
}

void checkers::print_pos() {
    cout << "My positions: " << endl;
    for (const auto& pr : my_pos) printf("%d %d, ", pr.first, pr.second);
    cout << endl;
    cout << "Rival positions: " << endl;
    for (const auto& pr : rival_pos) printf("%d %d, ", pr.first, pr.second);
    cout << endl;
}

bool checkers::exist_capturing() {
    avail_cap.clear();
    avail_move.clear();

    for (const auto& pr : my_pos) {
        if (getvalue(pr) == WHOSTURN) {
            exist_capturing_handling(pr, forward_dir_vec, 2);
        } else if (getvalue(pr) == toupper(WHOSTURN)) {
            exist_capturing_handling(pr, all_dir_vec, 4);
        }
    }
    return !avail_cap.empty();
}

vector<POINT> checkers::exist_capturing_handling(const POINT& pr,
                                                 POINT* move_dir, int sz) {
    vector<POINT> cap_ret;
    for (int i = 0; i < sz; i++) {
        POINT next = pr + move_dir[i];
        POINT next_next = next + move_dir[i];

        if (is_inboundary(next) && getvalue(next) == BLANK) {
            avail_move.insert(pr);
        }
        if (!is_inboundary(next) || !is_inboundary(next_next)) continue;
        if ((getvalue(next) == RIVAL || getvalue(next) == toupper(RIVAL)) &&
            getvalue(next_next) == BLANK) {
            avail_cap.insert(pr);
            cap_ret.push_back(next);
        }
    }

    return cap_ret;
}

vector<POINT> checkers::next_move_handling(const POINT& pr, POINT* move_dir,
                                           int sz) {
    vector<POINT> cap_ret;
    for(int i=0; i < sz; i++){
        POINT next = pr + move_dir[i]; 

        if(is_inboundary(next) && getvalue(next) == BLANK){
            cap_ret.push_back(next); 
        }
    }

    return cap_ret; 
}