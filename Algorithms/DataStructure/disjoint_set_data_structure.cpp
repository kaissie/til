#include <iostream>
#include <vector>

struct UnionFind {
  std::vector<int> roots;
  UnionFind(int N) : roots(N) {
    for (size_t i = 0; i < N; i++)
      roots[i] = i;
  }

  int root(int x) {
    if(roots[x] == x)
      return x;
    return roots[x] = root(roots[x]);
  }

  void unite(int x, int y) {
    int root_x = root(x);
    int root_y = root(y);
    if (root_x != root_y)
      roots[root_x] = root_y;
  }

  bool same(int x, int y) {
    return root(x) == root(y);
  }

  void print() {
    for (size_t i = 0; i < roots.size(); i++) {
      std::cout << i <<" : " << roots[i] << '\n';
    }
  }
};

int main(int argc, char const *argv[]) {
  std::cout << "initialize" << '\n';
  UnionFind tree(10);
  tree.print();
  std::cout << "unite 0,1,2,3" << '\n';
  tree.unite(0,1);
  tree.unite(2,3);
  tree.unite(0,2);
  tree.print();
  std::cout << "same? 0 3" << '\n';
  std::cout <<std::boolalpha <<tree.same(0,3) << '\n';
  std::cout << "same? 0 8" << '\n';
  std::cout <<std::boolalpha <<tree.same(0,8) << '\n';
  return 0;
}
