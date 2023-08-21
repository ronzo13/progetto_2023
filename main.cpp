#include <iostream>

#include "sir.hpp"

int main() {
  Param param{};
  std::cout << "beta: ";
  std::cin >> param.beta;
  std::cout << "gamma: ";
  std::cin >> param.gamma;

  int new_s{};
  int new_i{};
  int new_r{};

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

  std::cout << "total: " << sir.get_total() << '\n';
  std::cout << "------" << '\n';

  std::vector<SIR> epidemic = sir.evolve(days);

  /* nel ciclo viene creato un ogetto di tipo SIR const&
  a ogni iterazione viene creato un alias costante del contenuto della cella del
  vettore
  vengono poi chiamate delle funzioni di questo alias costante (const&)
  */

  int day{};
  int size = epidemic.size();
  for (SIR const& _sir : epidemic) {
    // bisogna cambiare il nome di sir già usato sopra?
    std::cout << "day: " << day << '\n';
    std::cout << "s: " << _sir.get_s() << '\n';
    std::cout << "i: " << _sir.get_i() << '\n';
    std::cout << "r: " << _sir.get_r() << '\n';
    std::cout << "total: " << _sir.get_total() << '\n';
    std::cout << "------" << '\n';

    if (day <= size) {
      ++day;
    } else {
      std::cout << "the epidemic lasts for: " << day << " days" << '\n';
      break;
    }
  }
}