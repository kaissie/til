#include <iostream>

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

class DiffieHellmanKeyExchange{
public:
  long long int alice_public_key;
  long long int bob_public_key;
  DiffieHellmanKeyExchange(long long int p, long long int g, long long int a, long long int b){
    long long int x = modExp(g,a,p);
    long long int y = modExp(g,b,p);
    alice_public_key = modExp(y,a,p);
    bob_public_key = modExp(x,b,p);
  }
};

int main(int argc, char const *argv[]) {
  long long int p,g,a,b;
  std::cout << "Enter the values of p and g upon which Alice and Bob both will agree" << '\n';
  std::cin >> p >> g;
  std::cout << "Enter the Secret Integer for Alice : ";
  std::cin >> a;
  std::cout << "Enter the Secret Integer for Bob : ";
  std::cin >> b;
  DiffieHellmanKeyExchange dh(p,g,a,b);

  std::cout << "Alice's public key : " << dh.alice_public_key << '\n';
  std::cout << "Bob's public key : " << dh.bob_public_key << '\n';
  return 0;
}
