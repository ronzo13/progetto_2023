#include <vector>

#ifndef SIR_HPP
#define SIR_HPP

struct Param {
  double beta{};
  double gamma{};
};

struct State {
  double s{};
  double i{};
  double r{};

  State() = default;
  State(int, int, int);
};

class SIR {
 private:
  int m_total{};
  State m_state{};
  Param m_par{};

 public:
  SIR(State const&, Param const&);

  std::vector<State> evolve(int days);

  int get_total() const;
};

bool operator==(State const&, State const&);

#endif