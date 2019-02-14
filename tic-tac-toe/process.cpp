#include "ttt.hpp"

using namespace std;

int ttt::process(const string& str) {
    if (str.size() == 1) {
        whosturn = str[0];
        rival = 'X' + 'O' - whosturn;
        return 0;
    }

    for (int i = 0; i < board_size; i++) {
        board.push_back(str[i]);
    }

    if (board.size() == board_size * board_size) {
        next_move();
        return 1;
    }
    return 0;
}

void ttt::print_board() {
    cout << endl;
    for (int i = 0; i < board.size(); i++) {
        cout << board[i];
        if (i % board_size == board_size - 1) cout << endl;
    }
}

unordered_set<int> ttt::check_avail_play() {
    unordered_set<int> ret;
    for (int i = 0; i < board.size(); i++) {
        if (board[i] == blank) ret.insert(i);
    }
    return ret;
}

int ttt::next_move() {
    // hard-coding
    if (board == "_________") {
        printf("1 1\n");
        return 0;
    }
    if(board == "____X____" || board == "____O____"){
        printf("0 0\n"); 
        return 0; 
    }

    int idx = minimax(0, whosturn, true, -1000, 1000).first;
    printf("%d %d\n", idx / board_size, idx % board_size);
    return 0;
}