#include <iostream>

#include "sir.hpp"

int main() {
  Param param{};
  std::cout << "beta: ";
  std::cin >> param.beta;
  std::cout << "gamma: ";
  std::cin >> param.gamma;

  double new_s{};
  double new_i{};
  double new_r{};

  std::cout << "s: ";
  std::cin >> new_s;
  std::cout << "i: ";
  std::cin >> new_i;
  std::cout << "r: ";
  std::cin >> new_r;

  SIR sir{new_s, new_i, new_r, param};

  int days{};
  std::cout << "epidemic duration: ";
  std::cin >> days;

  std::cout << "total: " << sir.total() << '\n';
  std::cout << "------" << '\n';
  for (int j{}; j < days; ++j) {
    sir.evolve();
    int s = sir.get_s();
    int i = sir.get_i();
    int r = sir.get_r();
    std::cout << "s: " << s << '\n';
    std::cout << "i: " << i << '\n';
    std::cout << "r: " << r << '\n';
    std::cout << "total: " << sir.total() << '\n';
    std::cout << "------" << '\n';
  }
}