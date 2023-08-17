#ifndef SIR_HPP
#define SIR_HPP

struct Param {
  double beta{};
  double gamma{};
};

struct SIR {
  double s{};
  double i{};
  double r{};
};

class Status {
 private:
  Param m_par{};
  SIR m_sir{};
  int m_days{};

 public:
  Status(Param, SIR, int);

  bool check_state() const;

  void evolve();

  int total() const;

  int get_s() const;
  int get_i() const;
  int get_r() const;
};

#endif