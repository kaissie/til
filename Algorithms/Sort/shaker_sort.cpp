#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <utility>
#include <chrono>

std::vector<int> make_rand_array_unique(const size_t size, int rand_min, int rand_max) {
  std::vector<int> tmp;
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::uniform_int_distribution<int> distribution(rand_min, rand_max);

  if (rand_max - rand_min < size){
    std::cout << "too narrow range" << '\n';
    exit(1);
  }

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

std::vector<int> shaker_sort(std::vector<int> & v) {
  std::vector<int> result = v;
  size_t head = 0;
  size_t tail = v.size() - 1;

  while(true) {
    for (size_t i = head; i < tail; ++i)
      if (result[i] > result[i+1])
        std::swap(result[i],result[i+1]);
    tail--;
    if (head == tail) break;
    for (size_t i = tail; i > head; --i)
      if (result[i] < result[i-1])
        std::swap(result[i],result[i-1]);
    head++;
    if (head == tail) break;
  }
  return result;
}


int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = shaker_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
  std::cout << '\n';
  return 0;
}
