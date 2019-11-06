#include <iostream>
#include <random>

long long int getRandom(long long int s, long long int e){
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::uniform_int_distribution<> dist(s, e);
  return dist(engine);
}
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

class ElGamalEncryption{
public:
  long long int decrypted_num;
  long long int encrypted_num[2];
  ElGamalEncryption(long long int p, long long int g, long long int a, long long int m){
    long long int h = modExp(g,a,p);
    // long long int h = 263;
    // long long int r = getRandom(0, p - 1);
    long long int r = 403;
    long long int c1 = modExp(g,r,p);
    long long int c2 = m*modExp(h,r,p) % p;
    encrypted_num[0] = c1;
    encrypted_num[1] = c2;
    decrypted_num = c2*modExp(c1,p-1-a,p) % p;
  }
};

int main(int argc, char const *argv[]) {
  long long int p,g,a,b,m;
  std::cout << "Enter the values of p and g for key generation" << '\n';
  std::cin >> p >> g;
  std::cout << "Enter the Secret Integer for Alice : ";
  std::cin >> a;
  std::cout << "Enter the Message to Bob : ";
  std::cin >> m;
  ElGamalEncryption eg(p,g,a,m);

  std::cout << "Encrypted Number : " << eg.encrypted_num[0] << "," << eg.encrypted_num[1] << '\n';
  std::cout << "Decrypted Number : " << eg.decrypted_num << '\n';
  return 0;
}
