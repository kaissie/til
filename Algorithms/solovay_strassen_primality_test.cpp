#include <iostream>
#include <random>

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
int modExp(int base, int power, int mod){
  int result = 1;
  while (power > 0) {
    if(power % 2 == 1)
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
  for(int i = 0; i < 20; ++i){
    // Generate a random number a
    int a = getRandom(2,num-1);
    int jacobian = (num + jacobi(a, num)) % num;
    int mod = modExp(a, (num - 1) / 2, num);

    if (!jacobian || mod != jacobian) {
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
