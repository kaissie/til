#include <iostream>
#include <random>
#include <string>
#include <time.h>
#include <algorithm>
#include <vector>
long long int getNbitRand(int n){
  // std::random_device seed_gen;
  // std::mt19937 engine(seed_gen());
  std::mt19937 engine((int)time(0));
  std::uniform_int_distribution<> dist(1<<(n-1) , (1<<n) - 1);
  return dist(engine);
}

void printCode(std::vector<int> code){
  std::cout << "<Text>" << '\n';
  for(char x: code)
      std::cout << x;
  std::cout << '\n';
  std::cout << "<Code>" << '\n';
  for(int x: code)
      std::cout << x << " ";
  std::cout << '\n';

}

class VernamCipher {
private:
  int key;
  int ciphernum;
  int planenum;

  void genKey(int k){
    key = getNbitRand(k);
    std::cout << "Generated key : "<< key << '\n';
  }
public:
  VernamCipher(int k) {
    genKey(k);
  }

  int encrypt(long long int m){
    ciphernum = m^key;
    // std::cout << "Encrypted num : "<< ciphertext << '\n';
    return ciphernum;
  }
  int decrypt(long long int c){
    planenum = c^key;
    // std::cout << "Decrypted num : "<< planetext << '\n';
    return planenum;
  }
};

int main(int argc, char const *argv[]) {
  int k,m,key;
  std::cout << "Enter security parameter : ";
  std::cin >> k;
  VernamCipher vc(k);
  std::string text = "The quick brown fox jumps over the lazy dog";
  auto code = std::vector<int>((int)text.size());
  auto cipher = std::vector<int>((int)text.size());
  auto decipher = std::vector<int>((int)text.size());

  std::transform(text.begin(),   text.end(),   code.begin(),     [](char x){return x;});
  std::transform(code.begin(),   code.end(),   cipher.begin(),   [&vc](char m){return vc.encrypt(m);});
  std::transform(cipher.begin(), cipher.end(), decipher.begin(), [&vc](char c){return vc.decrypt(c);});

  std::cout << "[Plain]" << '\n';
  printCode(code);
  std::cout << "\n]Cipher[-----------------------------------------" << '\n';
  printCode(cipher);
  std::cout << "\n]Decipher[-----------------------------------------" << '\n';
  printCode(decipher);





  return 0;
}
