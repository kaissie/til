#include "util.hpp"
#include <cmath>

std::vector<int> comb_sort(std::vector<int>& v) {
  std::vector<int> result = v;
  const size_t n = v.size();
  size_t h = std::floor(n / 1.3);
  bool changed = true;
  while (changed) {
    changed = false;
    for (size_t i = 0; i+h < n; ++i) {
      if (result[i] > result[i+h]){
        std::swap(result[i],result[i+h]);
        changed = true;
      }
    }
    if (h > 1)
      h = std::floor(h / 1.3);
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = comb_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
    std::cout << '\n';
  return 0;
}
