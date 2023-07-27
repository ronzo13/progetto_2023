#ifndef SIR_HPP
#define SIR_HPP

struct Param {
  double beta{};
  double gamma{};
};

class SIR {
 private:
  int m_s{};
  int m_i{};
  int m_r{};
  Param m_par{};

 public:
  SIR(int, int, int, Param);

  SIR evo(SIR &) const;

  int total() const;

  int get_s() const;
  int get_i() const;
  int get_r() const;
};

#endif