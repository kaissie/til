#include <iostream>
#include <vector>

using matrix = std::vector<std::vector<int>>;

matrix matMul(matrix a, matrix b) {
  int row_size = a.size();
  int col_size = b[0].size();
  matrix result(row_size, std::vector<int>(col_size, 0));

  for (size_t i = 0; i < row_size; i++)
    for (size_t j = 0; j < b.size(); j++)
      for (size_t k = 0; k < col_size; k++)
        result[i][j] += a[i][k] * b[k][j];
  return result;
}

matrix matExp(matrix base, int power){
  int row_size = base.size();
  int col_size = base.size();
  matrix result(row_size, std::vector<int>(col_size, 1));

  while (power > 0) {
    if(power & 1 == 1)
      result = matMul(result,base);
    base = matMul(base,base);
    power >>= 1;
  }
  return result;
}

std::vector<int> make_fibo_array(int size) {
  std::vector<int> result;
  if (size < 1) std::cout << "error: size is more than 0 (but this size is less than 1)" << '\n';
  if (size >= 1) result.push_back(1);
  if (size >= 2) result.push_back(1);

  matrix A{{1,1},{1,0}};
  for (size_t i = 0; i < size - 2; i++) {
    result.push_back(matExp(A, i+1)[1][0]);
  }
  return result;
}

int main(int argc, char const *argv[]) {
  std::vector<int> v = make_fibo_array(30);
  for(auto e: v)
    std::cout << e << ' ';
  return 0;
}
