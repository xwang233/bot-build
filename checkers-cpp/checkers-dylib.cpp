#include "checkers-dylib.h"
#include "checkers.hpp"

std::string point_to_json_array(const POINT& pt) {
    std::string str;
    str += '[';
    str += std::to_string(pt.first);
    str += ',';
    str += std::to_string(pt.second);
    str += ']';
    return str;
}

std::string checkers_process(std::string& board, const char player) {
    checkers chk;
    chk.setplayer(board.back());
    board.pop_back();
    chk.setboard(board);

    auto pttw = std::make_shared<TRANS_TABLE_HASH_MAP>();
    auto pttb = std::make_shared<TRANS_TABLE_HASH_MAP>();
    chk.setptt(pttb, pttw);

    // auto vp = chk.next_move_handling();
    auto vps = chk.minimax<&checkers::eval2>(0, player, true, -1000, 1000);
    auto vp = vps.first;
    if (vp.empty()) return "{\"mov\":null, \"act\":null, \"score\":null}";

    std::string ret;
    ret += "{\"mov\":[";
    const POINT* p_last = nullptr;
    for (const auto& p : vp) {
        if (p_last == nullptr) {
            p_last = &p;
            continue;
        }
        ret += '[';
        ret += point_to_json_array(*p_last);
        ret += ',';
        ret += point_to_json_array(p);
        ret += "],";
        p_last = &p;
    }
    ret.back() = ']';
    ret += ',';
    ret += "\"act\":";
    ret += (abs(vp[0].first - vp[1].first) == 1) ? "\"move\"" : "\"jump\"";
    ret += ','; 
    ret += "\"score\":"; 
    ret += std::to_string(vps.second); 
    ret += '}';

    return ret;
}