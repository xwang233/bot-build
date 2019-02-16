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
    const auto avail_moves = get_avail_move(player);
    const auto& avail_move = avail_moves.first;

    if (depth >= 12 && avail_moves.second == MOVE) return {{}, eval()};

    if (avail_move.empty()) {
#ifdef DEBUG4
        fprintf(stderr, "no avail move at depth = %d, player = %c\n", depth,
                player);
        print_board();
        cerr << endl;
#endif
        return {{}, player == WHOSTURN ? -1000 : 1000};
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
        const auto board_copy = board;
        for (const auto& vp : avail_move) {
            // auto moved = move_from_vp(vp, player);
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
            // recover_from_umap(moved);

            if (ret > best) {
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
        const auto board_copy = board;
        for (const auto& vp : avail_move) {
            // auto moved = move_from_vp(vp, player);
            move_from_vp(vp, player);
            auto rets = minimax(depth + 1, rival, true, alpha, beta);
            auto ret = rets.second;
#ifdef DEBUG2
            if (depth <= 2) {
                print_board();
                printf("depth = %d, player = %c, ret = %d\ntheplay: ", depth,
                       player, ret);
                for (const auto& p : vp) printf("%d %d, ", p.first, p.second);
                cout << endl;
                cout << endl;
            }
#endif
            board = board_copy;
            // recover_from_umap(moved);

            if (ret < worst) {
                bestplay = vp;
                worst = ret;
            }
            beta = min(beta, worst);
            if (alpha >= beta) break;
        }
#ifdef DEBUG
        printf("depth = %d, player = %c, eval func = %d\n", depth, player,
               worst);
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
            if (player == 'w' && c == 'w') eval_pawn += (board_size - i + 1);
        }
    }

    return eval_pawn + eval_king;
}

int checkers::eval() {
    char player = WHOSTURN;
    char rival = RIVAL;

    int eval_pawn = 0;
    int eval_king = 0;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            int c = board[i][j];
            if (c == BLANK) continue;

            if (c == toupper(player)) eval_king += (board_size + 2);
            if (player == 'b' && c == 'b') eval_pawn += (i + 1);
            if (player == 'w' && c == 'w') eval_pawn += (board_size - i + 1);

            if (c == toupper(rival)) eval_king -= (board_size + 2);
            if (rival == 'b' && c == 'b') eval_pawn -= (i + 1);
            if (rival == 'w' && c == 'w') eval_pawn -= (board_size - i + 1);
        }
    }

    const auto amps = get_avail_move(player);
    const auto amrs = get_avail_move(rival);
    const auto& amp = amps.first;
    const auto& amr = amrs.first;

    if (amp.empty()) return -1000;
    if (amr.empty()) return 1000;

    int eval_avail_move = 0;

    auto vpp = amp[0];
    if (amps.second == CAP)
        eval_avail_move += amp.size() * 3;
    else
        eval_avail_move += amp.size() * 1;

    auto vpr = amr[0];
    if (amrs.second == CAP)
        eval_avail_move -= amr.size() * 3;
    else
        eval_avail_move -= amr.size() * 1;

    return eval_pawn + eval_king + eval_avail_move;
}
