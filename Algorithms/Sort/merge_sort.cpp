#include "util.hpp"

void sorting(std::vector<int>& v, std::vector<int>& b, int head, int tail) {
  if(tail - head <= 1) return;
  int mid = (head + tail) / 2;
  sorting(v,b, head, mid);
  sorting(v,b, mid, tail);
  size_t i = head, j = mid;
  size_t buf_i = 0;
  while ( i < mid && j < tail) {
    if (v[i] < v[j])
      b[buf_i++] = v[i++];
    else
      b[buf_i++] = v[j++];
  }
  if (i == mid) {
    while (j < tail)
      b[buf_i++] = v[j++];
  } else {
    while (i < mid)
      b[buf_i++] = v[i++];
  }
  for (size_t l = 0; l < buf_i; l++)
    v[head + l] = b[l];
}

std::vector<int> merge_sort(std::vector<int>& v) {
  std::vector<int> result = v;
  const size_t n = v.size();
  std::vector<int> buffer(n);
  int head = 0, tail = n;
  sorting(result, buffer, head, tail);
  return result;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v1 = make_rand_array_unique(13,0,100);
  for(auto e: v1)
    std::cout << e << ' ';
  std::cout << '\n';
  std::vector<int> v2 = merge_sort(v1);
  for(auto e: v2)
    std::cout << e << ' ';
    std::cout << '\n';
  return 0;
}
