#include <iostream>
#include <random>
double mc(int trial_num) {
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    int count = 0;
    for (size_t i = 0; i < trial_num; ++i) {
      double x = dist(engine);
      double y = dist(engine);
      if (x*x + y*y < 1.0) count++;
    }
    return ((double)count/(double)trial_num)*4;
}

int main(int argc, char const *argv[]) {
  int times;
  while (true) {
    std::cout << "How many trial" << '>';
    std::cin >> times;
    if (times == 0) break;
    std::cout << mc(times) << '\n';
  }

  return 0;
}
