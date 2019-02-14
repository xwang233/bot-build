#ifndef PAIR_AS_POINT_H
#define PAIR_AS_POINT_H

#include <map>

typedef std::pair<int, int> point;
inline point operator+(const point& a, const point& b) {
    return {a.first + b.first, a.second + b.second};
}
inline point operator-(const point& a, const point& b) {
    return {a.first - b.first, a.second - b.second};
}
inline point operator*(const point& a, int b) { return {a.first * b, a.second * b}; }
inline point operator*(int b, const point& a) { return a * b; }

#endif