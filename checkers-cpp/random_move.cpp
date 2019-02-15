#include <random>
#include "checkers.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    ;

    const vector<string> board = {"_b_b_b_b", "b_b_b_b_", "_b_b_b_b",
                                  "________", "________", "w_w_w_w_",
                                  "_w_w_w_w", "w_w_w_w_"};

    int total_match = 100;
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
    printf("minimax win %d, tie %d, lose %d\n", minimax_win, tied,
           total_match - minimax_win - tied);
}

vector<POINT> checkers::random_move() {
    const auto avail_move = get_avail_move(WHOSTURN);

    if (avail_move.empty()) return {};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution uid(0, static_cast<int>(avail_move.size()) - 1);

    int rn = uid(gen);
    auto it = avail_move.begin();
    advance(it, rn);

    auto vp = *it;
    return vp;
}