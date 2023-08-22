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

  bool valid_input{false};
  do {
    std::cout << "s: ";
    std::string input;
    std::cin >> input;
    try {
      double check_s = std::stod(input);  // qui avviene il troncamento
      // riparte anche se inserisco int
      if (check_s == static_cast<int>(check_s)) {
        new_s = static_cast<int>(check_s);
        valid_input = true;
      } else {
        std::cout << "Invalid value for s. Please enter a valid integer."
                  << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid value for s. Please enter a valid integer." << '\n';
    }
  } while (!valid_input);

  // std::cout << "s: ";
  // std::cin >> new_s;
  std::cout << "i: ";
  std::cin >> new_i;
  std::cout << "r: ";
  std::cin >> new_r;

  State state(new_s, new_i, new_r);
  SIR sir{state, param};

  int days{};
  std::cout << "epidemic duration: ";
  std::cin >> days;

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

    if (day <= size) {
      ++day;
    } else {
      break;
    }
  }
  std::cout << "the epidemic lasts for: " << day - 1 << " days" << '\n';
}