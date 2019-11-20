#include <iostream>
#include <ctime>

class XorShift {
private:
  struct dictionary {
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t w;
  };
public:
  static const struct dictionary defaults = {
    123456789,
    362436069,
    521288629,
    88675123
  };
  uint32_t rand_count = 0;
  struct dictionary seeds;

  XorShift(uint32_t w=time(nullptr), uint32_t x=NULL, uint32_t y=NULL,uint32_t z=NULL) {
    x = x != NULL ? x : w<<13;
    y = y != NULL ? y : (w>>9)^(x<<6);
    z = z != NULL ? z : y>>7;
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

  static inline XorShift defaultSeed(){
    return XorShift(defaults.w, defaults.x, defaults.y, defaults.z);
  }

};


int main(int argc, char const *argv[]) {
  auto r_def=XorShift::defaultSeed();

  return 0;
}
