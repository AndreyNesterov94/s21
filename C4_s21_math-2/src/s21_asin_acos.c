#include "s21_math.h"

long double s21_asin(double x) {
  long double res = 0;
  if (x != x || x < -1 || x > 1) {
    res = S21_NAN;
  } else if (x == 1) {
    res = S21_PI / 2;
  } else if (x == -1) {
    res = -S21_PI / 2;
  } else {
    res = s21_atan(x / s21_sqrt(1 - x * x));
  }

  return res;
}

long double s21_acos(double x) {
  long double res = 0;
  if (x != x || x < -1 || x > 1) {
    res = S21_NAN;
  } else if (x == 1) {
    res = 0;
  } else if (x == -1) {
    res = S21_PI;
  } else if (x == 0) {
    res = S21_PI / 2;
  } else {
    res = s21_atan(s21_sqrt(1 - x * x) / x);
    if (x < 0) {
      res += S21_PI;
    }
  }

  return res;
}
