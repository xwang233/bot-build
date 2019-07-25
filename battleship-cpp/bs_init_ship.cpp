#include "battleship.hpp"

using namespace std;

string battleship::place_ship(vector<string>& board, int boat_size) {
    while (1) {
        point head = {randx(), randx()};
        while (getpoint(board, head) != '-') {
            head = {randx(), randx()};
        }

        if (boat_size == 1) {
            // board[head.first][head.second] = 'A';
            setpoint(board, head) = 'A';
            return to_string(head.first) + ' ' + to_string(head.second);
        }

        int direction = rand() % 4;
        point dir_vec = dir_vec_map[direction];

        point tail = head + (dir_vec * (boat_size - 1));

        if (is_inboundary(tail)) {
            bool possible = true;
            for (int i = 1; i < boat_size; i++) {
                point check = head + (dir_vec * i);
                if (getpoint(board, check) != '-') possible = false;
            }

            if (possible) {
                for (int i = 0; i < boat_size; i++) {
                    point check = head + (dir_vec * i);
                    // board[check.first][check.second] = 'A';
                    // setpoint(board, check) = 'A';
                    setpoint(board, check) = 'A' + ship_id;
                }
                string ret;
                ret += to_string(head.first) + ' ' + to_string(head.second);
                ret += ':';
                ret += to_string(tail.first) + ' ' + to_string(tail.second);

                ship_id++; 

                return ret;
            }
        }
    }
    return "";
}

string battleship::place_ship_size_one(vector<string>& board, bool iseven) {
    while (1) {
        point head = {randx(), randx()};
        if (getpoint(board, head) != '-') continue;

        if (iseven && (head.first + head.second) % 2 == 1) continue;
        if (!iseven && (head.first + head.second) % 2 == 0) continue;

        setpoint(board, head) = 'A' + ship_id;
        ship_id++; 
        return to_string(head.first) + ' ' + to_string(head.second);
    }
}

void battleship::ship_init_helper(vector<string>& strret,
                                  vector<string>& vviret) {
    vector<string> init_board =
        vector<string>(board_size, string(board_size, '-'));

    vector<string> ret;
    // ret.push_back(place_ship(init_board, 1));
    // ret.push_back(place_ship(init_board, 1));
    // ret.push_back(place_ship_size_one(init_board, true));
    // ret.push_back(place_ship_size_one(init_board, false));
    ret.push_back(place_ship(init_board, 2));
    ret.push_back(place_ship(init_board, 2));
    ret.push_back(place_ship(init_board, 3));
    ret.push_back(place_ship(init_board, 4));
    ret.push_back(place_ship(init_board, 5));

    // for (const auto& i : init_board) cout << i << endl;

    strret = ret;
    vviret = move(init_board);
}

vector<string> battleship::ship_init() {
    vector<string> res;
    vector<string> vviret;
    ship_init_helper(res, vviret);

    return res;
}

vector<vector<int>> battleship::ship_init_str() {
    vector<string> res;
    vector<string> vviret;
    ship_init_helper(res, vviret);

    // for (auto& str : res) cout << str << endl; 

    auto vires = vector<vector<int>>(board_size, vector<int>(board_size, 0));
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (vviret[i][j] == '-') {
                vires[i][j] = 0;
            } else {
                vires[i][j] = vviret[i][j] - 'A';
            }
        }
    }

    return vires;
}