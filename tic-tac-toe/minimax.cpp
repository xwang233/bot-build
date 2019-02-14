#include "ttt.hpp"

using namespace std;

#define DEBUG

pair<int, int> ttt::minimax(int depth, char c, bool maximizing, int alpha,
                            int beta) {
    if (depth == 25) return {-1, 0};

    if (is_wining(whosturn)) {
#ifdef DEBUG
        print_board();
        printf("depth = %d, player = %c, maximizing? = %s, winning\n", depth, c,
               maximizing ? "true" : "false");
#endif
        return {-1, 100 - depth};
    }
    if (is_wining(rival)) {
#ifdef DEBUG
        print_board();
        printf("depth = %d, player = %c, maximizing? = %s, losing\n ", depth, c,
               maximizing ? "true" : "false");
#endif
        return {-1, -100 + depth};
    }
    if (is_tie()) {
#ifdef DEBUG
        print_board();
        printf("depth = %d, player = %c, maximizing? = %s, tied\n ", depth, c,
               maximizing ? "true" : "false");
#endif
        return {-1, 0};
    }

    auto avail_play = check_avail_play();
    int the_play;

    int c_rival = 'X' + 'O' - c;
    if (maximizing) {
        int best = -1000;
        for (const auto& i : avail_play) {
            board[i] = c;
            int ret = minimax(depth + 1, c_rival, false, alpha, beta).second;
            board[i] = blank;
            if (ret > best) {
                best = ret;
                the_play = i;
            }
            alpha = max(alpha, best);
            if (beta <= alpha) {
#ifdef DEBUG
                print_board();
                printf("pruned, alpha = %d, beta = %d\n", alpha, beta);
#endif
                break;
            }
        }
#ifdef DEBUG
        print_board();
        printf(
            "depth = %d, player = %c, maximizing? = %s, best play at %d %d, "
            "possible max value = % d\n ",
            depth, c, "true", the_play / board_size, the_play % board_size,
            best);
#endif
        return {the_play, best};
    } else {
        int worst = 1000;
        for (const auto& i : avail_play) {
            board[i] = c;
            int ret = minimax(depth + 1, c_rival, true, alpha, beta).second;
            board[i] = blank;
            if (ret < worst) {
                worst = ret;
                the_play = i;
            }
            beta = min(beta, worst);
            if (beta <= alpha) break;
        }
#ifdef DEBUG
        print_board();
        printf(
            "depth = %d, player = %c, maximizing? = %s, best play at %d %d, "
            "possible min value = %d\n ",
            depth, c, "false", the_play / board_size, the_play % board_size,
            worst);
#endif
        return {the_play, worst};
    }
}