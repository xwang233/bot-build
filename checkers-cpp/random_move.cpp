#include <random>
#include "checkers.hpp"
#include <cstdlib> 
#include <ctime> 

using namespace std;

int main(int argc, char* argv[]) {
    const vector<string> board = {"_b_b_b_b", "b_b_b_b_", "_b_b_b_b",
                                  "________", "________", "w_w_w_w_",
                                  "_w_w_w_w", "w_w_w_w_"};

    srand(time(NULL)); 

    int total_match = 256;
    int minimax_win = 0;
    int tied = 0;
#pragma omp parallel for reduction(+ : minimax_win, tied)
    for (int i = 0; i < total_match; i++) {
        checkers chk_minimax;
        checkers chk_random;

        chk_minimax.setplayer('b');
        chk_random.setplayer('w');

        chk_random.setboard(board);
        chk_minimax.setboard(board);

        int step = 0;
        while (1) {
            auto vp1 = chk_minimax.next_move_handling();
            if (vp1.empty()) {
                // cout << "random win at " << step << endl;
                // chk_minimax.print_board();
                break;
            }
            chk_minimax.move_from_vp(vp1, chk_minimax.getplayer());
            chk_random.setboard(chk_minimax.getboard());

            auto vp = chk_random.random_move();
            if (vp.empty()) {
                // cout << "minimax win at " << step << endl;
                // chk_random.print_board();
                minimax_win++;
                break;
            }
            chk_random.move_from_vp(vp, chk_random.getplayer());
            chk_minimax.setboard(chk_random.getboard());

            step++;
            if (step >= 100) {
                // cout << "tied" << endl;
                tied++;
                break;
            }
        }
    }
    printf("minimax win rate %f, tie rate %f\n",
           (double)minimax_win / total_match, (double)tied / total_match);
}

int main2() {
    /*
    const string board = {
        "_b_b___b______b_____________b_b______w__w___w____w_____ww_______"};
    const string board =
        "_b_b___b______b_______________b_________w___w_b__w_____ww_______";
        */
    const string board =
        "_b_b_b_b______b______w______b___________w___w____w___w_ww_______";
    checkers chk;
    chk.setboard(board);
    chk.setplayer('b');
    chk.print_board();

    /*
    const auto rets = chk.get_avail_move('w');
    cout << (rets.second == chk.CAP ? "CAP" : "MOVE") << endl;
    const auto& ret = rets.first;
    for (const auto& vp : ret) {
        for (const auto& pt : vp) printf("%d %d, ", pt.first, pt.second);
        cout << endl;
    }
    chk.print_board();
    */

    /*
    vector<vector<POINT>> cap;
    vector<POINT> cur_vec = {{6, 7}};
    chk.get_next_cap({6, 7}, cap, cur_vec, 'w');
    for (const auto& vp : cap) {
        for (const auto& pt : vp) printf("%d %d, ", pt.first, pt.second);
        cout << endl;
    }
    */

    auto vp = chk.next_move_handling();
    for (const auto& pt : vp) printf("%d %d, ", pt.first, pt.second);
    cout << endl;

    return 0;
}

vector<POINT> checkers::random_move() {
    const auto avail_moves = get_avail_move(WHOSTURN);
    const auto& avail_move = avail_moves.first;

    if (avail_move.empty()) return {};

    int rn = rand() % avail_move.size(); 
    auto it = avail_move.begin();
    advance(it, rn);

    auto vp = *it;
    return vp;
}