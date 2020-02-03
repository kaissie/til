#include <iostream>
#include <vector>
#include <random>

using board_type = std::vector<std::vector<int>>;

bool isSafe(board_type& board, int row, int col) {
  size_t n = board.size();
  for(int i = 0; i < col; ++i)
    if(board[row][i])
      return false;
  for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
    if (board[i][j])
      return false;
  for (int i = row, j = col; j >= 0 && i < n; ++i, --j)
      if (board[i][j])
        return false;
  return true;
}

bool solve(board_type& board, int col) {
  size_t n = board.size();
  if (col >= n) return true;
  for(int i = 0; i < n; ++i) {
    if (isSafe(board, i, col)) {
      board[i][col] = 1;
      if(solve(board, col + 1))
        return true;
      board[i][col] = 0;
    }
  }
  return false;
}

void solve_n_queen(board_type& board) {
  if(!solve(board, 0))
    std::cout << "Solution does not exist" << '\n';
}

board_type make_board(int n) {
  std::vector<std::vector<int>> vec;
  vec.assign(n, std::vector<int>(n, 0));
  return vec;
}

void print_board(board_type v) {
  for(auto &row: v) {
    for(auto &cell: row) std::cout << cell << ' ';
    std::cout << '\n';
  }
}

int main(int argc, char const *argv[]) {
  board_type v = make_board(8);
  solve_n_queen(v);
  print_board(v);
  return 0;
}
