#include "util.hpp"

std::vector<int> selection_sort(std::vector<int>& v) {
  std::vector<int> result = v;
  const size_t n = v.size();
  for (size_t i = 0; i < n - 1; i++) {
    int min_idx = i;
    for (size_t j = i; j < n; j++)
      if (result[j] < result[min_idx]) min_idx = j;
    std::swap(result[i], result[min_idx]);
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = selection_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
    std::cout << '\n';
  return 0;
}
