#include "ttt.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    ttt t;
    string str;
    while (cin >> str) {
        if (t.process(str)) break;
    }
    return 0;
}