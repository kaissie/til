#include <algorithm>
#include <utility>

#include "util.hpp"


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
