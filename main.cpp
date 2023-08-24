#include <iostream>

#include "sir.hpp"
#include "validate_input.hpp"

int main() {
  Param param{};
  double beta{}, gamma{};
  param.beta = valid_beta(beta);
  param.gamma = valid_gamma(gamma);

  valid_R0(param);

  int new_s{}, new_i{}, new_r{};
  int s = valid_s(new_s);
  int i = valid_i(new_i);
  int r = valid_r(new_r);
  State state(s, i, r);
  SIR sir{state, param};

  int new_days{};
  int days = valid_days(new_days);

  std::cout << "total: " << sir.get_total() << '\n';
  std::cout << "------" << '\n';

  std::vector<State> epidemic = sir.evolve(days);

  int day{};
  int size = epidemic.size();
  for (auto const& _sir : epidemic) {
    std::cout << "day: " << day << '\n';
    std::cout << "s: " << _sir.s << '\n';
    std::cout << "i: " << _sir.i << '\n';
    std::cout << "r: " << _sir.r << '\n';
    std::cout << "total: " << _sir.s + _sir.i + _sir.r << '\n';
    std::cout << "------" << '\n';

    if (day < size) {
      ++day;
    } else {
      break;
    }
  }
  std::cout << "the epidemic lasts for: " << day - 1 << " days" << '\n';
}