#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double res = 0;
  if (x != x || y != y || x == S21_INF || x == S21_N_INF || y == 0) {
    res = S21_NAN;
  } else if (y == S21_INF || y == S21_N_INF) {
    res = x;
  } else {
    res = x - s21_trunc(x / y) * y;
  }

  return res;
}