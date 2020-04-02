#include <iostream>
#include <vector>

const int* binary_search(std::vector<int> array, int value) {
  int lower = 0;
  int upper = array.size();

  while( lower <= upper) {
    int mid = (lower + upper) / 2;
    if( array[mid] == value )
      return &array[mid];
    else if( array[mid] < value)
      lower = mid + 1;
    else
      upper = mid - 1;
  }
  return nullptr;
}
int main(int argc, char const *argv[]) {
  std::vector<int> v{-4, -1, 0, 3, 7, 9, 16};
  for(int i = -5; i <= 5; ++i){
    const int* p = binary_search( v, i );
    if( p == nullptr )
      std::cout << "Found:" << i << '\n';
    else
      std::cout << "Not Found:" << i << '\n';
  }

  return 0;
}
