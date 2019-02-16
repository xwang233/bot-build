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

    if (depth >= 6 && avail_moves.second == MOVE) return {{}, eval2()};

    if (avail_move.empty()) {
#ifdef DEBUG4
        fprintf(stderr, "no avail move at depth = %d, player = %c\n", depth,
                player);
        print_board();
        cerr << endl;
#endif
        return {{}, player == WHOSTURN ? -1000 : +1000};
    }
#ifdef DEBUG1
    print_board();
    printf("depth = %d, player = %c", depth, player);
    cerr << endl;
    cerr << (avail_moves.second == CAP ? "CAP" : "MOVE") << endl;
    for (const auto& vp : avail_move) {
        for (const auto& pt : vp)
            fprintf(stderr, "%d %d, ", pt.first, pt.second);
        cerr << endl;
    }
    cerr << endl;
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
        printf("\ndepth = %d, player = %c, best eval func = %d\n", depth,
               player, best);
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
        printf("\ndepth = %d, player = %c, worst eval func = %d\n", depth,
               player, worst);
        for (const auto& pt : bestplay) printf("%d %d, ", pt.first, pt.second);
        cout << endl;
        print_board();
#endif
        return {bestplay, worst};
    }
    return {};
}

// eval(WHOSTURN)-eval(RIVAL), depth 6, 0.78 WR, 0.11 TR
// eval(WHOSTURN), depth 6, 0.64 WR, 0.22 TR
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

// eval(), depth 3, 0.79 WR, 0.02 TR
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

// reference: https://github.com/kevingregor/Checkers
int checkers::eval2() {
    const char player = WHOSTURN;
    const char rival = RIVAL;
    const char uplayer = toupper(player);
    const char urival = toupper(rival);

    const float piece = 5.0;
    const float king = 7.75;
    const float backrow = 4.0;
    const float midmid = 2.5;
    const float midside = 0.5;
    const float vulnerable = -3.0;
    const float protected_value = 3.0;

    unordered_map<char, int> scores = {{player, 0}, {rival, 0}};

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            char c = board[i][j];
            if (c == BLANK) continue;

            // piece value
            if (c == uplayer || c == urival) scores[tolower(c)] += king;

            if (c == player || c == rival) {
                // regular piece value
                scores[c] += piece;

                // protected piece value
                /*
                POINT cur = {i, j};
                for (int i = 0; i < 2; i++) {
                    POINT next = cur + forward_dir_vec[c][i];
                    if (!is_inboundary(next)) continue;
                    if (getvalue(next) == c || getvalue(next) == toupper(c))
                        scores[c] += protected_value;
                }
                */
            }

            if (c == uplayer || c == urival) {
                char lc = tolower(c);
                scores[lc] += king;

                /*
                POINT cur = {i, j};
                for (int i = 0; i < 4; i++) {
                    POINT next = cur + all_dir_vec[i];
                    if (!is_inboundary(next)) continue;
                    if (getvalue(next) == c || getvalue(next) == lc)
                        scores[lc] += protected_value;
                }
                */
            }

            // back row value
            if ((c == 'w' && i == board_size - 1) || (c == 'b' && i == 0))
                scores[c] += backrow;

            // 4 slots in the mid-mid value
            if ((i == 3 && j == 2) || (i == 3 && j == 4) ||
                (i == 4 && j == 3) || (i == 4 && j == 5))
                scores[tolower(c)] += midmid;

            // 4 slots in the mid-side value
            if ((i == 3 && j == 0) || (i == 3 && j == 6) ||
                (i == 4 && j == 1) || (i == 4 && j == 7))
                scores[tolower(c)] += midside;
        }
    }

    const auto amp = get_avail_move(player);
    const auto amr = get_avail_move(rival);

    // vulnerable value
    // and protected value?
    if (amp.second == CAP) {
        const auto& vvp = amp.first;
        int num_of_vulnerable = 0;
        for (const auto& vp : vvp) num_of_vulnerable += vp.size() - 1;
        scores[rival] += vulnerable * num_of_vulnerable;
    }
    if (amr.second == CAP) {
        const auto& vvp = amr.first;
        int num_of_vulnerable = 0;
        for (const auto& vp : vvp) num_of_vulnerable += vp.size() - 1;
        scores[player] += vulnerable * num_of_vulnerable;
    }

    return scores[player] - scores[rival];
}