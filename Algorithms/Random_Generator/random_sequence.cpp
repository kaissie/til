#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

std::vector<int> make_rand_array_unique(const size_t size, int rand_min, int rand_max) {
  std::vector<int> tmp;
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::uniform_int_distribution<int> distribution(rand_min, rand_max);

  const size_t make_size = static_cast<size_t>(size*1.2);

  while(tmp.size() < size){
      while(tmp.size() < make_size)
        tmp.push_back(distribution(engine));

      std::sort(tmp.begin(), tmp.end());
      auto unique_end = std::unique(tmp.begin(), tmp.end());

      if(size < std::distance(tmp.begin(), unique_end))
          unique_end = std::next(tmp.begin(), size);

      tmp.erase(unique_end, tmp.end());
  }

  std::shuffle(tmp.begin(), tmp.end(), engine);
  return std::move(tmp);

}


int main(int argc, char const *argv[]) {
  auto seq = make_rand_array_unique(10,1,100);
  for(auto x: seq) {
    std::cout << x << ' ';
  }
  return 0;
}
