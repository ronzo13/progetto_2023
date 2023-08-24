#include "validate_input.hpp"

#include <iostream>
#include <string>

#include "sir.hpp"

/*se il primo if non funziona il programma riparte, continue indica che va
avanti e riparte il while *il try catch serve a gestire principalmente
l'inserimento di caratteri che non sono numeri se sei inseriscono numeri non
consentiti il messaggio di errore parte ad opera dell'else, altrimenti se si
inserisce un carattere il messaggio di errore parte ad opera del catch, sono
quindi entrambi necessari*/

double valid_beta() {
  bool valid_input{false};
  double beta{};
  while (!valid_input) {
    std::cout << "beta: ";
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
    std::cout << "gamma: ";
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
 *is greater than 1 fot the epidemic to
 * start*/
void valid_R0(Param& par) {
  while (par.beta <= par.gamma) {
    std::cout << "Since beta < gamma the R0 index is less than 1" << '\n';
    std::cout << "Please insert beta greater than gamma" << '\n';
    par.beta = valid_beta();
    par.gamma = valid_gamma();
  }
  std::cout << "Since beta > gamma, R0 > 1, the epidemic starts" << '\n';
}

int valid_s() {
  bool valid_input{false};
  int new_s{};
  while (!valid_input) {
    std::cout << "s: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout << "Invalid value for beta. Please use a dot (.) as the "
                   "decimal separator."
                << '\n';
      continue;  // Ask for input again
    }
    try {
      // qui avviene il troncamento se uso stoi() o dichiato int
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
    std::cout << "i: ";
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
    std::cout << "r: ";
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
    std::cout << "epidemic duration : ";
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

double valid_S_percentage() {
  bool valid_input{false};
  double p_s{};
  while (!valid_input) {
    std::cout << "S percentage: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout
          << "Invalid value for S percentage. Please use a dot (.) as the "
             "decimal separator."
          << '\n';
      continue;
    }
    try {
      double check_p_s = std::stod(input);
      if (check_p_s >= 0 && check_p_s <= 1) {
        p_s = check_p_s;
        valid_input = true;
      } else {
        std::cout << "Invalid value for S percentage. Please enter a number "
                     "between 0 and 1."
                  << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid value for S percentage. Please enter a number "
                   "between 0 and 1."
                << '\n';
    }
  }
  return p_s;
}

double valid_I_percentage() {
  bool valid_input{false};
  double p_i{};
  while (!valid_input) {
    std::cout << "I percentage: ";
    std::string input;
    std::cin >> input;
    if (input.find(',') != std::string::npos) {
      std::cout
          << "Invalid value for I percentage. Please use a dot (.) as the "
             "decimal separator."
          << '\n';
      continue;
    }
    try {
      double check_p_i = std::stod(input);
      if (check_p_i >= 0 && check_p_i <= 1) {
        p_i = check_p_i;
        valid_input = true;
      } else {
        std::cout << "Invalid value for I percentage. Please enter a number "
                     "between 0 and 1."
                  << '\n';
      }
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid value for I percentage. Please enter a number "
                   "between 0 and 1."
                << '\n';
    }
  }
  return p_i;
}
