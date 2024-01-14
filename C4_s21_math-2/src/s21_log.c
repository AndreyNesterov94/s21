#include "s21_math.h"

long double s21_log(double x) {
  long double res = 0;
  if (x != x || x == S21_N_INF || x < 0) {
    res = S21_NAN;
  } else if (x == 0) {
    res = S21_N_INF;
  } else if (x == S21_INF) {
    res = x;
  } else {
    long double y_start = 0;
    int invert = 0;
    if (x < 1) {
      invert = 1;
      x = 1 / x;
    }
    long double y_end = x;
    while (s21_fabs(s21_exp(res) - x) > 1e-6) {
      res = (y_start + y_end) / 2;
      if (s21_exp(res) > x) {
        y_end = res;
      } else {
        y_start = res;
      }
    }
    res = invert ? -res : res;
  }
  return res;
}