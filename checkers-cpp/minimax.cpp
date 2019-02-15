#include "checkers.hpp"

using namespace std;

// #define DEBUG
// #define DEBUG1
// #define DEBUG2
// #define DEBUG3
// #define DEBUG4

pair<vector<POINT>, int> checkers::minimax(int depth, char player,
                                           bool maximizing, int alpha,
                                           int beta) {
    if (depth == 10) return {{}, eval(WHOSTURN) - eval(RIVAL)};

    const auto avail_move = get_avail_move(player);
    if (avail_move.empty()) {
#ifdef DEBUG4
        printf("no avail move at depth = %d, player = %c\n", depth, player);
        print_board();
        cout << endl;
#endif
        return {{}, eval(WHOSTURN) - eval(RIVAL)};
    }
#ifdef DEBUG1
    print_board();
    printf("depth = %d, player = %c", depth, player);
    cout << endl;
    for (const auto& vp : avail_move) {
        for (const auto& pt : vp) printf("%d %d, ", pt.first, pt.second);
        cout << endl;
    }
#endif

    char rival = 'w' + 'b' - player;
    vector<POINT> bestplay;
    if (maximizing) {
        int best = -10000;
        auto board_copy = board;
        for (auto& vp : avail_move) {
            move_from_vp(vp, player);
            auto rets = minimax(depth + 1, rival, false, alpha, beta);
            auto ret = rets.second;
#ifdef DEBUG2
            if (depth <= 3) {
                // print_board();
                printf("depth = %d, player = %c, ret = %d\ntheplay: ", depth,
                       player, ret);
                for (const auto& p : vp) printf("%d %d, ", p.first, p.second);
                cout << endl;
                cout << endl;
            }
#endif
            board = board_copy;

            if (ret > best) {
#ifdef DEBUG3
                if (best != -10000)
                    printf("depth = %d,best = %d, ret = %d\n", depth, best,
                           ret);
#endif
                bestplay = vp;
                best = ret;
            }
            alpha = max(alpha, best);
            if (alpha >= beta) break;
        }
#ifdef DEBUG
        printf("depth = %d, player = %c, eval func = %d\n", depth, player,
               best);
        for (const auto& pt : bestplay) printf("%d %d, ", pt.first, pt.second);
        cout << endl;
        print_board();
#endif
        return {bestplay, best};
    } else {
        int worst = 10000;
        auto board_copy = board;
        for (auto& vp : avail_move) {
            move_from_vp(vp, player);
            auto rets = minimax(depth + 1, rival, true, alpha, beta);
            auto ret = rets.second;
#ifdef DEBUG2
            if (depth <= 3) {
                // print_board();
                printf("depth = %d, player = %c, ret = %d\ntheplay: ", depth,
                       player, ret);
                for (const auto& p : vp) printf("%d %d, ", p.first, p.second);
                cout << endl;
                cout << endl;
            }
#endif
            board = board_copy;

            if (ret < worst) {
#ifdef DEBUG3
                if (worst != 10000)
                    printf("depth = %d, worst = %d, ret = %d\n", depth, worst,
                           ret);
#endif
                bestplay = vp;
                worst = ret;
            }
            beta = min(beta, worst);
            if (alpha >= beta) break;
        }
#ifdef DEBUG
        printf("depth = %d, player = %c, eval func = %d\n", depth, player,
               best);
        for (const auto& pt : bestplay) printf("%d %d, ", pt.first, pt.second);
        cout << endl;
        print_board();
#endif
        return {bestplay, worst};
    }
    return {};
}

int checkers::eval(char player) {
    int eval_pawn = 0;
    int eval_king = 0;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            int c = board[i][j];
            if (c == BLANK) continue;

            if (c == toupper(player)) eval_king += (board_size + 2);
            if (player == 'b' && c == 'b') eval_pawn += (i + 1);
            if (player == 'w' && c == 'w') eval_pawn += (board_size - i + 2);
        }
    }

    return eval_pawn + eval_king;
}
