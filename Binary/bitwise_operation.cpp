#include <iostream>
#include <bitset>

void printb(uint32_t num) {
  std::cout <<std::bitset<8>(num) << '\n';
}

void bitbasic() {
  uint32_t a = 9, b = 10;
  std::cout << "a   : ";
  printb(a);
  std::cout << "b   : ";
  printb(b);
  std::cout << "a&b : ";
  printb(a&b);
  std::cout << "a|b : ";
  printb(a|b);
  std::cout << "a^b : ";
  printb(a^b);
  std::cout << "a<<1: ";
  printb(a<<1);
  std::cout << "b>>1: ";
  printb(b>>1);
  std::cout << "~a  : ";
  printb(~a);
}

int main(int argc, char const *argv[]) {
  bitbasic();
  return 0;
}
