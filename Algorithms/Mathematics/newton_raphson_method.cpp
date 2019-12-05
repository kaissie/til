#include <iostream>
template<class Func1, typename Func2>
double newton_raphson_method (double x0, Func1 f, Func2 fd, int k) {
  double x = x0;
  for (size_t i = 0; i < k; i++) {
    x = x - (f(x) / fd(x));
    std::cout << x << '\n';
  }
  return x;
}

int main(int argc, char const *argv[]) {
  auto func =  [] (double x)-> double {return x*x - 2;};
  auto funcd =  [] (double x)-> double {return 2*x;};

  double result = newton_raphson_method(1,func,funcd,4);
  std::cout << "square root of 2 >> "<< result << '\n';
  return 0;
}
