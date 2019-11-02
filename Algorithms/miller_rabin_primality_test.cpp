#include <iostream>
#include <random>

int modExp(int base, int power, int mod){
  int result = 1;
  while (power > 0) {
    if(power & 1 == 1)
      result = (result * base) % mod;
    base = (base * base) % mod;
    power >>= 1;
  }
  return result;
}

int getRandom(int s, int e){
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::uniform_int_distribution<> dist(s, e);
  return dist(engine);
}

bool isPrime(int num){
  if (num == 2) return true;
  if (num % 2 == 0 || num < 2) return false;
  bool result = true;
  int d = num-1;
  while (d % 2 == 0) d >>= 1;
  for(int i = 0; i < 20; ++i){
    int a = getRandom(1,num-1);
    int t = d;
    int y = modExp(a,t,num);
    while (t != num-1 && y != 1 && y != num-1) {
      y = (y * y) % num;
      t <<= 1;
    }
    if(y != num - 1 && t % 2 == 0) {
      result = false;
      break;
    }
  }
  return result;
}

int main(int argc, char const *argv[]) {
  /* code */
  int num = 2;
  for(int i = 2; i < 10000; ++i){
    if(isPrime(i)) std::cout << i << ' ';
  }
  // std::cout << num << " is "<< (isPrime(num) ?  "probably prime" : "composite") << '\n';
  return 0;
}
