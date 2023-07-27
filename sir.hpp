#ifndef SIR_HPP
#define SIR_HPP

struct Param {
  double beta{};
  double gamma{};
};

//guardando anche lab7 credo sia meglio fare SIR come struct piuttosto che coma class
//però mi serve qualche conferma magari sento Luca

class SIR {
 private:
  int s_{};
  int i_{};
  int r_{};

 public:
  SIR(int, int, int);

  int sum() const { return s_ + i_ + r_; };
};

class Evolve {
 private:
  SIR sir_;
  Param par_{};

 public:
  Evolve(SIR &);
};

#endif