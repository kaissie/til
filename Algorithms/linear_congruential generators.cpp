#include <iostream>

class LCGs {
private:
  struct dictionary { uint32_t x; uint32_t a; uint32_t b; uint32_t m;};
  uint32_t x;
  uint32_t a;
  uint32_t b;
  uint32_t m;
public:
  static const struct dictionary defaults;
  uint32_t rand_count = 0;
  struct dictionary seeds;

  LCGs(uint32_t x=defaults.x, uint32_t a=defaults.a, uint32_t b=defaults.b,uint32_t m=defaults.m) {
    seeds={x,a,b,m};
    this->x=x;this->a=a;this->b=b;this->m=m;
  }

  uint32_t rand() {
    rand_count ++;
    this->x = (this->a * this->x + this->b) % this->m;
    return this->x;
  }
};
const struct LCGs::dictionary LCGs::defaults={
  123456789,
  48271,
  0,
  4294967295
};

int main(int argc, char const *argv[]) {
  auto r=LCGs();
  std::cout << "LCGs" << '\n';
  std::cout << r.rand() << '\n';
  for (size_t i = 0; i < 10; i++) {
    std::cout << r.rand() << '\n';
  }
  return 0;
}
