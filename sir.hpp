#ifndef SIR_HPP
#define SIR_HPP

struct Param {
  double beta{};
  double gamma{};
};

class SIR {
 private:
  int s_{};
  int i_{};
  int r_{};
  Param par_{};

 public:
  SIR(int s, int i, int r, double beta, double gamma)
      : s_{s}, i_{i}, r_{r}, par_{beta, gamma} {}

  int sum() const { return s_ + i_ + r_; };

  int evo_s(int &s, int &i, double &beta);

  int evo_i();

  int evo_r();
};

#endif