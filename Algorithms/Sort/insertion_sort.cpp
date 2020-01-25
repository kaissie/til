#include "util.hpp"

std::vector<int> insertion_sort(std::vector<int>& v) {
  std::vector<int> result = v;
  const size_t n = v.size();
  for (size_t i = 1; i < n; ++i) {
    if (result[i-1] > result[i]) {
      int j = i-1;
      while (j >= 0 && result[j] > result[i]) --j;
      int tmp = result[i];
      result.erase(result.cbegin()+i);
      result.insert(result.cbegin()+j+1, tmp);
    }
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = insertion_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
    std::cout << '\n';
  return 0;
}
