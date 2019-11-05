#include <iostream>

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

int gcd(int a, int b) {
  if (a < b) return gcd(b, a);
  if (b != 0)
    return gcd(b, a % b);
  else
    return a;
}

int lcm(int a, int b) {
  return a*b / gcd(a,b);
}

class RivestShamirAdleman{
public:
  long long int decrypted_num;
  long long int encrypted_num;
  RivestShamirAdleman(long long int p, long long int q, int m){
    int e,d;
    int n = p*q;
    int l = lcm(p-1, q-1);
    for(int i = 2; i < l; ++i){
      if(gcd(i,l) == 1){
        e = i;
        break;
      }
    }
    for(int i = 2; i < l; ++i){
      if(e*i % l == 1){
        d = i;
        break;
      }
    }
    encrypted_num  = modExp(m,e,n);
    decrypted_num  = modExp(encrypted_num,d,n);

  }
};

int main(int argc, char const *argv[]) {
  long long int p,q,m;

  std::cout << "Enter the values of p and q for to make public key" << '\n';
  std::cin >> p >> q;
  std::cout << "Enter the Message to Bob : ";
  std::cin >> m;

  RivestShamirAdleman rsa(p,q,m);

  std::cout << "Encrypted Number : " << rsa.encrypted_num << '\n';
  std::cout << "Decrypted Number : " << rsa.decrypted_num << '\n';
  return 0;
}
