#include <iostream>
#include <vector>

const int* linear_search(std::vector<int> array, int value) {
  for(auto &a : array) {
    if(a == value)
      return &a;
  }
  return nullptr;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v{-4, -1, 0, 3, 7, 9, 16};
  for(int i = -5; i <= 5; ++i){
    const int* p = linear_search( v, i );
    if( p == nullptr )
      std::cout << "Found:" << i << '\n';
    else
      std::cout << "Not Found:" << i << '\n';
  }

  return 0;
}
