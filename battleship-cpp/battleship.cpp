#include "battleship.hpp"

using namespace std;

int battleship::process(string str) {
    if (str == "INIT") {
        vector<string> ret = ship_init();

        for (const auto& i : ret) cout << i << endl;
        return 1;
    }

    if (!initiated && str == to_string(board_size)) {
        initiated = true;
        cur_board = {};
        return 0;
    }

    if (initiated) {
        return read_handle(str);
    }

    return 0;
}

int battleship::read_handle(string str) {
    cur_board.push_back(str);

    if (cur_board.size() == board_size) {
        initiated = false;
        // point ret = hit_ship_fully_random(cur_board);
        point ret = hit_ship_adjacent_random(cur_board);

        cout << ret.first << " " << ret.second << endl;
        return 1;
    } else {
        return 0;
    }
}