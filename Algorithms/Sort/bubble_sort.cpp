#include <algorithm>
#include "util.hpp"

std::vector<int> bubble_sort(std::vector<int> v) {
  std::vector<int> result = v;
  for(size_t j = 0; j < v.size(); j++) {
    for (size_t i = 0; i < v.size() - j - 1; i++) {
      if (result[i] > result[i+1]) {
        int tmp = result[i];
        result[i] = result[i+1];
        result[i+1] = tmp;
      }
    }
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = bubble_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
  std::cout << '\n';
  return 0;
}
