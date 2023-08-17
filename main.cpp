#include <iostream>

#include "sir.hpp"

int main() {
  Param param{};
  std::cout << "beta: ";
  std::cin >> param.beta;
  std::cout << "gamma: ";
  std::cin >> param.gamma;

  SIR sir{};
  std::cout << "s: ";
  std::cin >> sir.s;
  std::cout << "i: ";
  std::cin >> sir.i;
  std::cout << "r: ";
  std::cin >> sir.r;

  int days{};
  std::cout << "durata epidemia: ";
  std::cin >> days;

  Status Status{param, sir, days};
  int s = Status.get_s();
  int i = Status.get_i();
  int r = Status.get_r();
  std::cout << "totale: " << Status.total() << '\n';
  std::cout << "------" << '\n';
  for (int j{}; j < days; ++j) {
    Status.evolve();
    s = Status.get_s();
    i = Status.get_i();
    r = Status.get_r();
    std::cout << "s: " << s << '\n';
    std::cout << "i: " << i << '\n';
    std::cout << "r: " << r << '\n';
    std::cout << "totale: " << Status.total() << '\n';
    std::cout << "------" << '\n';
  }
}