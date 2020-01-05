#include <iostream>
#include <utility>
int gcd(int a, int b){
  if(b > a) std::swap(a,b);
  while(b != 0){
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main(int argc, char const *argv[]) {
  std::cout << "Please enter two numbers" << '\n';
  int a,b;
  std::cin >> a >> b;
  std::cout << "greatest common divisor : "<< gcd(a,b) << '\n';
  return 0;
}
