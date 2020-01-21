#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <random>
#include <iostream>

std::vector<int> make_rand_array_unique(const size_t size, const int rand_min, const int rand_max) {
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

#endif
