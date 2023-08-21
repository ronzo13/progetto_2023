#include <vector>

#ifndef SIR_HPP
#define SIR_HPP

struct Param {
  double beta{};
  double gamma{};
};

class SIR {
 private:
  double m_s{};
  double m_i{};
  double m_r{};
  int m_total{};
  Param m_par{};

 public:
  SIR(int, int, int, Param const&);

  bool check_param() const;
  bool check_state() const;

  std::vector<SIR> evolve(int days);

  int get_total() const;

  int get_s() const;
  int get_i() const;
  int get_r() const;
};

bool operator==(SIR const&, SIR const&);

#endif