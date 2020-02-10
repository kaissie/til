#include <iostream>
#include <string>

std::string fizzbuzz(const int& n) {
  std::string s = "";
  if (n % 3 == 0) s += "Fizz";
  if (n % 5 == 0) s += "Buzz";
  if (!s.size()) s += std::to_string(n);
  return s;
}

int main(int argc, char const *argv[]) {
  for (size_t i = 1; i < 100; ++i) {
    std::cout << fizzbuzz(i) << '\n';
  }
  return 0;
}
