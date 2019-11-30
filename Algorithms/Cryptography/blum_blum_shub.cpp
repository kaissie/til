#include <iostream>
#include <bitset>
class BBS {
private:
  struct dictionary { uint32_t x; uint32_t p; uint32_t q;};
  uint32_t x;
  uint32_t p;
  uint32_t q;
  uint32_t m;
  int digits;
public:
  static const struct dictionary defaults;
  uint32_t rand_count = 0;
  struct dictionary seeds;

  BBS(uint32_t n, uint32_t x=defaults.x, uint32_t p=defaults.p, uint32_t q=defaults.q) {
    seeds={x,p,q};
    this->digits = n;
    this->m = p * q;
    this->x=x; this->p=p; this->q=q;
  }

  uint32_t rand() {
    uint32_t number = 0;
    rand_count ++;

    for (size_t i = 0; i < this->digits; i++) {
      this->x = (this->x * this->x) % this->m;
      // std::cout << "num : " << this->x << '\n';
      number = (number << 1) | (this->x & 1);
    }
    return number;
  }
};
const struct BBS::dictionary BBS::defaults={
  1234,
  7263,
  9591
};

int main(int argc, char const *argv[]) {
  auto r=BBS(8,5);
  std::cout << "BBS" << '\n';
  // std::cout << r.rand() << '\n';
  for (size_t i = 0; i < 109; i++) {
    std::cout << r.rand() << '\n';
  }
  return 0;
}
