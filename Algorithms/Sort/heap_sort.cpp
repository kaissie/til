#include <cmath>
#include <utility>

#include "util.hpp"


void make_heap_structure(std::vector<int>& v, int n) {
  int parent = std::floor((n - 1) / 2);
  int a = parent;
  while (a >= 0) {
    int left_leaf = 2 * parent + 1;
    int right_leaf = left_leaf + 1;
    int top = left_leaf;
    if(right_leaf < n)
      if(v[right_leaf] > v[left_leaf]) top = right_leaf;
    if (left_leaf < n && v[parent] < v[top]){
      std::swap(v[parent],v[top]);
      parent = top;
    } else {
      a -= 1;
      parent = a;
    }
  }
}

std::vector<int> heap_sort(std::vector<int> & v) {
  std::vector<int> result = v;
  for (size_t i = result.size(); i > 1; --i) {
    make_heap_structure(result, i);
    std::swap(result[0], result[i-1]);
  }
  return result;
}


int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = heap_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
  std::cout << '\n';
  return 0;
}
