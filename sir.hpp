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
  Param m_par{};

 public:
  SIR(double, double, double, Param const&);

  bool check_param() const;
  bool check_state() const;

  void evolve();

  int total() const;

  int get_s() const;
  int get_i() const;
  int get_r() const;
};

#endif