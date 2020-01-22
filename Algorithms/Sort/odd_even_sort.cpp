#include <algorithm>
#include <utility>

#include "util.hpp"

std::vector<int> odd_even_sort(std::vector<int> & v) {
  std::vector<int> result = v;
  bool changed = true;
  while (changed) {
    changed = false;
    for (size_t i = 0; i < v.size() - 1; i+=2) {
      if (result[i] > result[i+1]){
        std::swap(result[i],result[i+1]);
        changed = true;
      }
    }
    for (size_t i = 1; i < v.size() - 1; i+=2) {
      if (result[i] > result[i+1]){
        std::swap(result[i],result[i+1]);
        changed = true;
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
  std::vector<int> v2 = odd_even_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
  std::cout << '\n';
  return 0;
}
