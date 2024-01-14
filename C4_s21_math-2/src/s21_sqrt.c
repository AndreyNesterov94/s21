#include "s21_math.h"

int s21_isnan(double x) { return (x != x); }

long double s21_sqrt(double x) {
  // Проверяем на негативное значение или NaN, и возвращаем S21_NAN в таких
  // случаях
  if (x < 0 || s21_isnan(x)) {
    return S21_NAN;
  }
  // Если x равен нулю или бесконечности, возвращаем x
  else if (x == 0 || x == S21_INF) {
    return x;
  }

  // Начальное приближение x0: половина x
  long double x0 = x / 2;

  // Итеративное уточнение значения
  while (1) {
    // Считаем новое приближение x1
    long double x1 = (x0 + x / x0) / 2;
    // можно устновить точность.
    if (s21_fabs(x1 - x0) < 1e-16) {
      return x1;
    }
    x0 = x1;
  }
}
