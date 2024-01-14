#include "s21_math.h"

long double s21_exp(double x) {
  long double res = 0;
  if (x != x || x == S21_INF) {
    res = x;
  } else if (x == S21_N_INF) {
    res = 0;
  } else {
    res = 1;
    long double last_res = 0;
    int fact_cntr = 1;
    long double term = 1;

    while (s21_fabs(res - last_res) > 1e-6) {
      last_res = res;

      term *= (long double)x / fact_cntr;
      res += term;
      fact_cntr++;
    }
  }

  return res;
}