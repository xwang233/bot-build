#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

enum class Move { UP, DOWN, LEFT, RIGHT };
const Move g_moves[4] = {Move::UP, Move::DOWN, Move::LEFT, Move::RIGHT};
const std::unordered_map<Move, std::pair<int, int>> g_move_dir = {
    {Move::UP, {-1, 0}},
    {Move::DOWN, {1, 0}},
    {Move::LEFT, {0, -1}},
    {Move::RIGHT, {0, 1}}};
const std::unordered_map<Move, std::string> g_move_str = {
    {Move::UP, "UP"},
    {Move::DOWN, "DOWN"},
    {Move::LEFT, "LEFT"},
    {Move::RIGHT, "RIGHT"}};

struct Board {
  std::vector<std::vector<int>> _board;
  std::unordered_map<int, std::pair<int, int>> _pos;
  int _steps_moved;
  std::vector<Move> _move_steps;

  int _size;

  Board(int a)
      : _board(std::vector<std::vector<int>>(a, std::vector<int>(a, 0))),
        _size(a), _steps_moved(0) {}
  Board(const Board &that) = default;
  Board(int a, std::vector<int> b) : Board(a) {
    if (a * a != b.size()) {
      throw std::runtime_error("input vector b (size " +
                               std::to_string(b.size()) +
                               ") is not square of a = " + std::to_string(a));
    }

    for (int i = 0; i < a * a; i++) {
      _board[i / a][i % a] = b[i];
    }

    init_pos();
  }

  void clean_steps() {
    _steps_moved = 0;
    _move_steps.clear();
  }

  void print() const {
    for (const auto &v : _board) {
      std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  bool can_move(Move m) const {
    const auto &pos0 = _pos.at(0);
    if (pos0.first == 0 && m == Move::UP)
      return false;
    if (pos0.first == _size - 1 && m == Move::DOWN)
      return false;
    if (pos0.second == 0 && m == Move::LEFT)
      return false;
    if (pos0.second == _size - 1 && m == Move::RIGHT)
      return false;

    return true;
  }

  void init_pos() {
    _pos.clear();
    for (int i = 0; i < _size; i++) {
      for (int j = 0; j < _size; j++) {
        _pos[_board[i][j]] = std::make_pair(i, j);
      }
    }
  }

  // user need to check can_move before calling move_()
  void move_(Move m) {
    auto pos0 = _pos.at(0);
    int npos_i = pos0.first + g_move_dir.at(m).first;
    int npos_j = pos0.second + g_move_dir.at(m).second;

    int val = _board[npos_i][npos_j];

    this->_board[npos_i][npos_j] = 0;
    this->_board[pos0.first][pos0.second] = val;

    this->_pos[0] = std::make_pair(npos_i, npos_j);
    this->_pos[val] = pos0;

    this->_steps_moved++;

    this->_move_steps.push_back(m);
  }

  Board move(Move m) const {
    if (!can_move(m))
      throw std::runtime_error("cannot move " + g_move_str.at(m));

    Board res(*this);
    res.move_(m);
    return res;
  }

  float heuristic() const {
    float dist = 0;
    int nb_displaced = 0;

    // Manhattan dist for all displaced block
    for (int i = 1; i < _size * _size; i++) {
      auto pos = _pos.at(i);

      if (pos.first == i / _size && pos.second == i % _size)
        continue;

      nb_displaced++;

      dist += abs(pos.first - i / _size);
      dist += abs(pos.second - i % _size);
    }

    // return _steps_moved + dist + std::sqrt(nb_displaced);
    return _steps_moved + dist;
  }

  bool is_target() const {
    for (int i = 1; i < _size * _size; i++) {
      const auto &posi = _pos.at(i);
      if (posi.first != i / _size || posi.second != i % _size) {
        return false;
      }
    }
    return true;
  }

  bool is_same_board(const Board &that) const {
    for (int i = 1; i < _size * _size; i++) {
      if (_pos.at(i) != that._pos.at(i))
        return false;
    }
    return true;
  }
  bool operator==(const Board &that) const { return is_same_board(that); }

  int &operator()(int i, int j) { return _board[i][j]; }
  const int &operator()(int i, int j) const { return _board[i][j]; }

  int &operator()(const std::pair<int, int> &pr) {
    return _board[pr.first][pr.second];
  }
  const int &operator()(const std::pair<int, int> &pr) const {
    return _board[pr.first][pr.second];
  }
};

Board reader() {
  int a = 0;
  std::cin >> a;

  auto res = Board(a);

  for (int i = 0; i < a * a; i++) {
    int x = 0;
    std::cin >> x;
    res(i / a, i % a) = x;
  }

  res.init_pos();

  return res;
}

void writer(const std::vector<Move> &res, bool steps_only = false) {
  std::cout << res.size() << std::endl;
  if (steps_only)
    return;

  for (const auto &m : res) {
    std::cout << g_move_str.at(m) << std::endl;
  }
}

struct BoardComparer {
  bool operator()(const Board &lhs, const Board &rhs) {
    return lhs.heuristic() > rhs.heuristic();
  }
};

template <> struct std::hash<Board> {
  std::size_t operator()(const Board &b) const {
    std::size_t s = b._board.size();

    std::size_t h = 0;
    for (size_t i = 1; i < s * s; i++) {
      h ^= (b._board[i / s][i % s] + i * 10);
    }
    return h;
  }
};

// A-Star
std::vector<Move> solver(Board &board) {
  std::priority_queue<Board, std::vector<Board>, BoardComparer> q;
  std::unordered_set<Board> visited;

  q.push(board);
  visited.insert(board);

  while (!q.empty()) {
    Board top = std::move(q.top());
    q.pop();

    if (top.is_target()) {
      //std::cout << visited.size() << " states searched" << std::endl;
      return top._move_steps;
    }

    for (const auto m : g_moves) {
      if (top.can_move(m)) {
        Board next = top.move(m);
        if (!visited.count(next)) {
          visited.insert(next);
          q.push(std::move(next));
        }
      }
    }
  }

  return Board(0)._move_steps;
}

Board random_board(int a) {
  std::random_device rd;
  std::mt19937_64 gen(rd());

  auto res = std::vector<int>(a * a, 0);
  for (int i = 0; i < a * a; i++) {
    res[i] = i;
  }

  auto b = Board(a, res);

  for (int i = 0; i < a * a * 10; i++) {
    auto m = g_moves[gen() % 4];
    if (b.can_move(m))
      b.move_(m);
  }

  b.clean_steps();

  return b;
}

int main() {
  // 3 0 3 8 4 1 7 2 6 5
  // auto board = reader();
  auto board = random_board(3);

  board.print();
  auto res = solver(board);
  writer(res);
}