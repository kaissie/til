#include "util.hpp"
#include <cmath>


std::vector<int> shell_sort(std::vector<int>& v) {
  std::vector<int> result = v;
  const size_t n = v.size();
  size_t gap = std::floor(n/2);
  for (size_t h = gap ; h > 0; h /= 2) {
    for(size_t i = h; i < n; i+=h) {
      if (result[i-h] > result[i]) {
        int j = i-h;
        while (j >= 0 && result[j] > result[j+h]){
          std::swap(result[j], result[j+h]);
          j -= h;
        }
      }
    }
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(8,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = shell_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
    std::cout << '\n';
  return 0;
}
