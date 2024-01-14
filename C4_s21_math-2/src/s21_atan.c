#include "s21_math.h"

long double s21_atan(double x) {
  long double res = 0;
  if (x != x) {
    res = x;
  } else if (x == S21_INF) {
    res = S21_PI / 2;
  } else if (x == S21_N_INF) {
    res = -S21_PI / 2;
  } else if (x == 1) {
    res = S21_PI / 4;
  } else if (x == -1) {
    res = -S21_PI / 4;
  } else if (x > 1) {
    res = S21_PI / 2 - s21_atan(1 / x);
  } else if (x < -1) {
    res = -S21_PI / 2 - s21_atan(1 / x);
  } else {
    long double term = x;
    int denom = 1;
    int sign = 1;
    while (s21_fabs(term / denom) > 1e-6) {
      res += sign * term / denom;
      sign *= -1;
      term *= x * x;
      denom += 2;
    }
  }

  return res;
}