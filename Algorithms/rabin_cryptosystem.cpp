#include <iostream>
#include <tuple>
#include <random>
#include <time.h>
int mod(int a, int m) {
  return (a % m + m) % m;
}

int extgcd(int a, int b, int &p, int &q) {
  if (b == 0){
    p = 1;
    q = 0;
    return a;
  }
 int d = extgcd(b, a%b, q, p);
  q -= a/b * p;
  return d;
}

std::tuple<int, int> crt(int b1, int m1, int b2, int m2) {
  int p, q;
  int d = extgcd(m1,m2,p,q);
  if ((b2 - b1) % d != 0)
    return {0, -1};
  int m = m1 * (m2/d);
  int tmp = (b2 - b1) / d * p % (m2 / d);
  int r = mod(b1 + m1 * tmp, m);
  return {r, m};
}

bool is_prime(int n){
  for (size_t i = 3; i*i < n; i += 2)
    if (n % i == 0)
      return false;
  return true;
}


int make_prime(int bit){
  std::mt19937 engine((int)time(0));
  std::uniform_int_distribution<> dist(1<<(bit-1) , (1<<bit) - 1);
  while(true){
    int n = dist(engine);
    n = 4*n + 3;
    if(is_prime(n)) return n;
  }
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


class RabinCryptosystem{
private:
  int p_key;
  int s_key[2];
  int ciphernum;
  int planenum;

  void genKey(int k){
    int p = make_prime(k);
    int q = p;
    while (p == q)
      q = make_prime(k);
    p_key = p*q;
    s_key[0] = p;
    s_key[1] = q;
  }

public:
  long long int decrypted_num;
  long long int encrypted_num;
  RabinCryptosystem(int k){
    this->genKey(k);
  }

  int encrypt(int m){
    ciphernum = (m*m) % p_key;
    return ciphernum;
  }

  std::tuple<int, int, int, int> decrypt(int c){
    int mp = modExp(c, (s_key[0]+1)/4, s_key[0]);
    int mq = modExp(c, (s_key[1]+1)/4, s_key[1]);
    std::tuple<int, int> m1,m2,m3,m4;
    m1 = crt(mp,s_key[0],mq,s_key[1]);
    m2 = crt(-mp,s_key[0],mq,s_key[1]);
    m3 = crt(mp,s_key[0],-mq,s_key[1]);
    m4 = crt(-mp,s_key[0],-mq,s_key[1]);
    return {std::get<0>(m1), std::get<0>(m2), std::get<0>(m3), std::get<0>(m4)};
  }
};

int main(int argc, char const *argv[]) {
  int k, m, c;
  crt(2,3,3,5);
  std::cout << "Enter the security parameter" << '\n';
  std::cin >> k;
  std::cout << "Enter the Message to Bob : ";
  std::cin >> m;

  RabinCryptosystem rabin(k);
  c = rabin.encrypt(m);
  std::cout << "Encrypted Number : " << c << '\n';
  auto dm = rabin.decrypt(c);
  std::cout << "Decrypted Number : " << std::get<0>(dm) << " " <<std::get<1>(dm)<< " " <<std::get<2>(dm)<< " " <<std::get<3>(dm) << '\n';
  return 0;
}
