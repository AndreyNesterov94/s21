#include "s21_math.h"

long double s21_fabs(double x) {
  long double res = 0;
  if (x != x || x == S21_INF) {
    res = x;
  } else if (x == S21_N_INF) {
    res = -x;
  } else if (x < 0) {
    res = -x;
  } else {
    res = x;
  }

  return res;
}
