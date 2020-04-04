#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <bitset>
using ci  = std::pair<char,int>;

std::vector<int> bitap(std::string text, std::string pattern) {
  std::map<char,int> mask;
  for(auto c: text) {
    if(!mask.contains(c))
      mask.insert(ci{c,0});
  }
  int finish = 1 << (pattern.size() - 1);
  for(auto pc: pattern) {
    for(auto &mk: mask) {
      mk.second >>= 1;
      if (pc == mk.first)
        mk.second |= finish;
    }
  }

  int state = 0;
  std::vector<int> ret;
  for (size_t i = 0; i < text.size(); i++) {
    state = (state << 1 | 1) & mask[text[i]];
    if((state & finish) == finish)
      ret.push_back(i);
  }
  return ret;
}

int main(int argc, char const *argv[]) {
  auto result = bitap("acbacbaca", "acbaca");
  for(auto n: result) {
    std::cout << n << '\n';
  }
  return 0;
}
