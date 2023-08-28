#include "sir.hpp"

#ifndef VALIDATE_INPUT_HPP
#define VALIDATE_INPUT_HPP

double valid_beta();

double valid_gamma();

void valid_R0(double&, double&);

int valid_s();

int valid_i();

int valid_r();

int valid_days();

int valid_side();

void valid_SIR(int&, int&, int);

#endif
