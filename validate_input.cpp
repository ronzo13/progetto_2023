#include "validate_input.hpp"

#include <iostream>
#include <string>

#include "sir.hpp"

double valid_beta() {
  bool valid_input{false};
  double beta{};
  while (!valid_input) {
    std::cout << "Insert beta: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout << "Invalid value for beta. Please use a dot (.) as the "
                   "decimal separator."
                << '\n';
      continue;
    }
    try {
      double check_beta = std::stod(input);
      if (check_beta >= 0 && check_beta <= 1) {
        beta = check_beta;
        valid_input = true;
      } else {
        std::cout
            << "Invalid value for beta. Please enter a number between 0 and 1."
            << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout
          << "Invalid value for beta. Please enter a number between 0 and 1."
          << '\n';
    }
  }
  return beta;
}

double valid_gamma() {
  bool valid_input{false};
  double gamma{};
  while (!valid_input) {
    std::cout << "Insert gamma: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout << "Invalid value for gamma. Please use a dot (.) as the "
                   "decimal separator."
                << '\n';
      continue;
    }
    try {
      double check_gamma = std::stod(input);
      if (check_gamma >= 0 && check_gamma <= 1) {
        gamma = check_gamma;
        valid_input = true;
      } else {
        std::cout
            << "Invalid value for gamma. Please enter a number between 0 and 1."
            << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout
          << "Invalid value for gamma. Please enter a number between 0 and 1."
          << '\n';
    }
  }
  return gamma;
}

/*the function checks that R0 = beta/gamma
 *is greater than 1 for the epidemic to
 * start*/
void valid_R0(double& beta, double& gamma) {
  while (beta <= gamma) {
    std::cout << "Since beta < gamma, R0 <= 1." << '\n';
    std::cout << "Please insert beta greater than gamma." << '\n';
    beta = valid_beta();
    gamma = valid_gamma();
  }
  std::cout << "Since beta > gamma, R0 > 1, the epidemic starts." << '\n';
}

int valid_s() {
  bool valid_input{false};
  int new_s{};
  while (!valid_input) {
    std::cout << "Insert susceptibles: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout << "Invalid value for beta. Please use a dot (.) as the "
                   "decimal separator."
                << '\n';
      continue;
    }
    try {
      double check_s = std::stod(input);
      if (check_s == static_cast<int>(check_s) && check_s >= 0) {
        new_s = static_cast<int>(check_s);
        valid_input = true;
      } else {
        std::cout << "Invalid value for s. Please enter a valid integer."
                  << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid value for s. Please enter a valid integer." << '\n';
    }
  }
  return new_s;
}

int valid_i() {
  bool valid_input{false};
  int new_i{};
  while (!valid_input) {
    std::cout << "Insert infectious: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout << "Invalid value for i. Please use a dot (.) as the "
                   "decimal separator."
                << '\n';
      continue;
    }
    try {
      double check_i = std::stod(input);
      if (check_i == static_cast<int>(check_i) && check_i >= 0) {
        new_i = static_cast<int>(check_i);
        valid_input = true;
      } else {
        std::cout << "Invalid value for i. Please enter a valid integer."
                  << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid value for i. Please enter a valid integer." << '\n';
    }
  }
  return new_i;
}

int valid_r() {
  bool valid_input{false};
  int new_r{};
  while (!valid_input) {
    std::cout << "Insert removed: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout << "Invalid value for r. Please use a dot (.) as the "
                   "decimal separator."
                << '\n';
      continue;
    }
    try {
      double check_r = std::stod(input);
      if (check_r == static_cast<int>(check_r) && check_r >= 0) {
        new_r = static_cast<int>(check_r);
        valid_input = true;
      } else {
        std::cout << "Invalid value for r. Please enter a valid integer."
                  << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid value for r. Please enter a valid integer." << '\n';
    }
  }
  return new_r;
}

int valid_days() {
  bool valid_input{false};
  int new_days{};
  while (!valid_input) {
    std::cout << "Insert epidemic duration in days: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout
          << "Invalid value for epidemic duration. Please use a dot (.) as the "
             "decimal separator."
          << '\n';
      continue;
    }
    try {
      double check_days = std::stod(input);
      if (check_days == static_cast<int>(check_days) && check_days >= 0) {
        new_days = static_cast<int>(check_days);
        valid_input = true;
      } else {
        std::cout << "Invalid value for epidemic duration. Please enter a "
                     "valid integer."
                  << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid value for epidemic duration. Please enter a valid "
                   "integer."
                << '\n';
    }
  }
  return new_days;
}

int valid_side() {
  bool valid_input{false};
  int new_side{};
  while (!valid_input) {
    std::cout << "Insert grid side: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout << "Invalid value for grid side. Please use a dot (.) as the "
                   "decimal separator."
                << '\n';
      continue;
    }
    try {
      double check_side = std::stod(input);
      if (check_side == static_cast<int>(check_side) && check_side >= 0) {
        new_side = static_cast<int>(check_side);
        valid_input = true;
      } else {
        std::cout << "Invalid value for grid side. Please enter a "
                     "valid integer."
                  << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid value for gird side. Please enter a valid "
                   "integer."
                << '\n';
    }
  }
  return new_side;
}

void valid_SIR(int& s, int& i, int side) {
  while ((side * side) < (s + i)) {
    std::cout << "Since (S + I) > (side * side) the grid cannot be filled."
              << '\n';
    std::cout << "Please insert again S and I." << '\n';
    s = valid_s();
    i = valid_i();
  }
  std::cout << "Since (S + I) <= (side * side) the epidemic starts." << '\n';
}