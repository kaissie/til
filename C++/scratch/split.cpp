#include <iostream>
#include <vector>
#include <string>

template <typename T>
void print_vec(std::vector<T> v) {
  for(auto e: v)
    std::cout << e << ' ';
  std::cout << '\n';
}

template <typename T>
std::vector<std::string> split(const std::string& s, const T& separator, bool ignore_empty = 0, bool split_empty = 0)
{
  struct {
    auto len(const std::string&             s) { return s.length(); }
    auto len(const std::string::value_type* p) { return p ? std::char_traits<std::string::value_type>::length(p) : 0; }
    auto len(const std::string::value_type  c) { return c == std::string::value_type() ? 0 : 1; /*return 1;*/ }
  } util;

  if (s.empty()) {
    if (!split_empty || util.len(separator)) return {""};
    return {};
  }

  auto v = std::vector<std::string>();
  auto n = static_cast<std::string::size_type>(util.len(separator));
  if (n == 0) {    /// empty separator ///
    if (!split_empty) return {s};
    for (auto&& c : s) v.emplace_back(1, c);
    return v;
  }

  auto p = std::string::size_type(0);
  while (1) {      /// split with separator ///
    auto pos = s.find(separator, p);
    if (pos == std::string::npos) {
      if (ignore_empty && p - n + 1 == s.size()) break;
      v.emplace_back(s.begin() + p, s.end());
      break;
    }
    if (!ignore_empty || p != pos)
      v.emplace_back(s.begin() + p, s.begin() + pos);
    p = pos + n;
  }
  return v;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v{0,1,2,3,4};
  std::string s = "1,2,3,4|5,6,7,8,9,10";
  print_vec(split(s,",|"));
  return 0;
}
