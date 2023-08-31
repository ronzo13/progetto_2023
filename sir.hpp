#ifndef SIR_HPP
#define SIR_HPP

#include <vector>

struct Param {
  double beta{};
  double gamma{};
};

struct State {
  double s{};
  double i{};
  double r{};

  State(int, int, int);
};

class SIR {
 private:
  int m_total{};
  State m_state;
  Param m_par;

 public:
  SIR(State const&, Param const&);

  int get_total() const;

  /* evolve the pandemic for the number of days inserted */
  std::vector<State> evolve(int);
};

bool operator==(State const&, State const&);

#endif