#include <iostream>
#include <vector>
#include <random>
void printMaze(std::vector<std::vector<char>> v) {
  for(auto row: v) {
    for(auto c: row)
      std::cout  << c << ' ';
    std::cout << '\n';
  }
}

long long int getRandom(long long int s, long long int e){
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::uniform_int_distribution<> dist(s, e);
  return dist(engine);
}

struct point {
  int x;
  int y;
};

void setpath(point p, std::vector<std::vector<char>>& maze, std::vector<point>& s_points) {
  maze[p.y][p.x] = ' ';
  if (p.x % 2 == 1 && p.y % 2 == 1)
    s_points.push_back(p);
}

bool setStartPoint(point& p, std::vector<point>& s_points) {
  if(s_points.size() == 0) return false;
  int index = getRandom(0, s_points.size() - 1);
  p = s_points[index];
  s_points.erase(s_points.begin() + index);
  return true;
}

void dig(point p, std::vector<std::vector<char>>& maze, std::vector<point>& s_points) {
  while (true) {
    std::vector<int> directions;
    if (p.x-2 >= 0 && maze[p.y][p.x-1] == '#' && maze[p.y][p.x-2] == '#')
      directions.push_back(0);
    if (p.y+2 < maze.size() && maze[p.y+1][p.x] == '#' && maze[p.y+2][p.x] == '#')
      directions.push_back(1);
    if (p.x+2 < maze.size() && maze[p.y][p.x+1] == '#' && maze[p.y][p.x+2] == '#')
      directions.push_back(2);
    if (p.y-2 >= 0 && maze[p.y-1][p.x] == '#' && maze[p.y-2][p.x] == '#')
      directions.push_back(3);

    if (directions.size() == 0) break;
    setpath(p, maze, s_points);
    int dir = getRandom(0, directions.size() - 1);
    switch (directions[dir]) {
      case 0:
        setpath({--(p.x), p.y}, maze, s_points);
        setpath({--(p.x), p.y}, maze, s_points);
        break;
      case 1:
        setpath({p.x, ++(p.y)}, maze, s_points);
        setpath({p.x, ++(p.y)}, maze, s_points);
        break;
      case 2:
        setpath({++(p.x), p.y}, maze, s_points);
        setpath({++(p.x), p.y}, maze, s_points);
        break;
      case 3:
        setpath({p.x, --(p.y)}, maze, s_points);
        setpath({p.x, --(p.y)}, maze, s_points);
        break;
    }
  }
  point sp;
  if(setStartPoint(sp, s_points))
    dig(sp, maze, s_points);
}

std::vector<std::vector<char>> makeMaze(size_t N) {
  std::vector<std::vector<char>> maze(N, std::vector<char>(N, '#'));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
        maze[i][j] = ' ';
  point p = {1, 1};
  std::vector<point> s_points;
  dig(p, maze, s_points);
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
        maze[i][j] = '#';
  return maze;
}

int main(int argc, char const *argv[]) {
  auto maze = makeMaze(11);
  printMaze(maze);
  return 0;
}
