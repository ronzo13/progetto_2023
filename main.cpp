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

  Status status{param, sir, days};
  std::cout << "totale: " << status.total() << '\n';
  std::cout << "------" << '\n';
  status.evolve();
}