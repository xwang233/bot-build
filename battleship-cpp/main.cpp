#include <ctime>

#include "battleship.hpp"

int main() {
    battleship bs;
    srand(time(NULL));

    std::string str;
    while (std::cin >> str) {
        int ret = bs.process(str);

        if (ret == 1) {
            break;
        } else
            continue;
    }
    return 0;
}