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

std::vector<std::vector<char>> makeMaze(size_t N) {
  std::vector<std::vector<char>> maze(N, std::vector<char>(N, ' '));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      size_t direction = 0;
      if (i == 0 || j == 0 || i == N - 1 || j == N - 1) {
        maze[i][j] = '#';
        continue;
      } else if (i == 2 && j % 2 == 0) {
        maze[i][j] = '#';
        direction = getRandom(0, 3);
      } else if (i % 2 == 0 && j % 2 == 0) {
        maze[i][j] = '#';
        direction = getRandom(0, 4);
      } else
        continue;

      while (true) {
        int wall_x = j, wall_y = i;
        switch (direction) {
          case 0:
            wall_x++;
            break;
          case 1:
            wall_y++;
            break;
          case 2:
            wall_x--;
            break;
          case 3:
            wall_y--;
            break;
        }
        if (maze[wall_y][wall_x] != '#') {
            maze[wall_y][wall_x] = '#';
            break;
        } else
          direction = getRandom(0, 4);
      }
    }
  return maze;
}

int main(int argc, char const *argv[]) {
  auto maze = makeMaze(11);
  printMaze(maze);
  return 0;
}
