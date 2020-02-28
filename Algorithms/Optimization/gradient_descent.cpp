#include <iostream>
#include <cmath>
#include <random>

long long int getRandom(long long int s, long long int e){
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::uniform_int_distribution<> dist(s, e);
  return dist(engine);
}

double f(double x, double y) {
  return x*x + y*y + x*y - 2*x;
}

double dfx(double x, double y) {
  return 2*x + y - 2;
}

double dfy(double x, double y) {
  return 2*y + x;
}

int main(int argc, char const *argv[]) {
  double alpha = 0.0001;
  double x = 1.0;
  double y = 1.0;
  double eps = 1.e-10;
  std::cout << "Value of f(x, y) at Step 0 is " << f(x, y) << '\n';
  while (f(x,y) > eps) {
    x = x - alpha * dfx (x, y);
    y = y - alpha * dfy (x, y);
  }
  std::cout << "Value of f(x, y) is " << f(x, y) << '\n';
  std::cout << "Result (x, y) = " <<"(" << x << ", " << y << ")" << '\n';
  return 0;
}
