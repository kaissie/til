#include <iostream>
#include <ctime>

class XorShift {
private:
  struct dictionary { uint32_t x; uint32_t y; uint32_t z; uint32_t w; };
  uint32_t x;
  uint32_t y;
  uint32_t z;
  uint32_t w;
  uint32_t t;
public:
  static const struct dictionary defaults;
  uint32_t rand_count = 0;
  struct dictionary seeds;

  XorShift(uint32_t w=defaults.w, uint32_t x=defaults.x, uint32_t y=defaults.y,uint32_t z=defaults.z) {
    x = x != 0 ? x : w<<13;
    y = y != 0 ? y : (w>>9)^(x<<6);
    z = z != 0 ? z : y>>7;
    seeds={x,y,z,w};
    this->w=w;this->x=x;this->y=y;this->z=z;
  }

  uint32_t rand() {
    rand_count ++;
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w^(w>>19)) ^ (t^(t>>8));
  }
};
const struct XorShift::dictionary XorShift::defaults={
  123456789,
  362436069,
  521288629,
  88675123
};

int main(int argc, char const *argv[]) {
  auto r=XorShift();
  std::cout << "XORShift" << '\n';
  for (size_t i = 0; i < 10; i++) {
    std::cout << r.rand() << '\n';
  }
  return 0;
}
