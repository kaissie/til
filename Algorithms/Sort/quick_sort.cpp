#include "util.hpp"
#include <cmath>


void sorting(std::vector<int>& v, int head, int tail, int n) {
  int pivot = v[head];
  int i = head, j = tail;
  if(tail - head <= 1) return;
  while (i != j) {
    if(v[i] >= pivot && v[j] <= pivot)
      std::swap(v[i],v[j]);
    else if (v[i] < pivot)
      i++;
    else if (v[j] > pivot)
      j--;
    if (i == j) {
      sorting(v, head, i, ++n);
      sorting(v, j+1, tail, ++n);
    };
  }

}

std::vector<int> quick_sort(std::vector<int>& v) {
  std::vector<int> result = v;
  int pivot = v[0];
  const size_t n = v.size();
  int head = 0, tail = n - 1;
  int i= 0, j = tail;
  sorting(result, head, tail, 0);
  return result;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = quick_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
    std::cout << '\n';
  return 0;
}
