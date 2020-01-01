#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


void printCode(std::vector<int> code){
  for(int x: code)
      std::cout << x << " ";
  std::cout << '\n';
}
void printText(std::vector<int> code){
  for(char x: code)
      std::cout << x << " ";
  std::cout << '\n';
}
std::vector<int> transcode(std::string text){
  auto code = std::vector<int>((int)text.size());
  std::transform(text.begin(), text.end(), code.begin(), [](int x){return x;});
  return code;
}

class SSC {
public:
  static std::vector<int> caesar(std::vector<int> code, int n = 1){
    std::vector<int> cipher = std::vector<int>((int)code.size());
    std::transform(code.begin(), code.end(), cipher.begin(), [&n](int x){return (x+n)%128;});
    return cipher;
  }
};


int main(int argc, char const *argv[]) {
  std::string text;
  getline(std::cin,text);
  std::vector<int> code = transcode(text);
  std::vector<int> cipher = SSC::caesar(code, 3);
  std::vector<int> decipher = SSC::caesar(cipher, -3);

  std::cout << "PLANE TEXT" << '\n';
  std::cout << text << '\n';
  std::cout << "code" << '\n';
  printCode(code);

  std::cout << "CIPHER" << '\n';
  printText(cipher);
  std::cout << "code" << '\n';
  printCode(cipher);

  std::cout << "DECIPHER" << '\n';
  printText(decipher);
  std::cout << "code" << '\n';
  printCode(decipher);
  return 0;
}
