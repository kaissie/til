#include <iostream>
#include <utility>
int jacobi(int a, int m) {
  int j = 1;
  while (a != 0) {
    while (a % 2 == 0) {
      a /= 2;
      if(m % 8 == 3 || m % 8 == 5) j *= -1;
    }
    std::swap(a,m);
    if (a % 4 == 3 && m % 4 == 3) j *= -1;
    a %= m;
  }
  if (m == 1) return j;
  else return 0;
}
int main(int argc, char const *argv[]) {
  int a,m;
  std::cout << "Enter an integer a and an odd number m." << '\n';
  std::cin >> a >> m;
  std::cout << "Result : " << jacobi(a,m);
  return 0;
}
