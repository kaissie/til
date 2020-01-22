#include <algorithm>
#include <utility>

#include "util.hpp"

std::vector<int> gnome_sort(std::vector<int> & v) {
  std::vector<int> result = v;
  for (size_t i = 1; i < v.size();) {
    if (result[i] >= result[i-1])
      ++i;
    else {
      std::swap(result[i],result[i-1]);
      if (i > 1) --i;
    }
  }
  return result;
}


int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = gnome_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
  std::cout << '\n';
  return 0;
}
