#ifndef SRC_S21_MATCH_H_
#define SRC_S21_MATCH_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_NAN (0.0 / 0.0)
#define S21_INF (1.0 / 0.0)
#define S21_N_INF (-1 * 1.0 / 0.0)
#define S21_PI 3.141592653589793238462643383279502884L
#define S21_EXP 2.718281828459045235360287471352662498L

typedef union {
  double data;
  struct {
    unsigned mantis1 : 32;
    unsigned mantis2 : 20;
    unsigned exponent : 11;
    unsigned sign : 1;
  } bits;
} double_cast;

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_pow(double base, double exp);
long double s21_floor(double x);
long double s21_ceil(double x);
long double s21_fmod(double x, double y);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_atan(double x);
long double s21_sqrt(double x);
long double s21_cos(double x);
long double s21_sin(double x);
long double s21_tan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
int s21_isnan(double x);

int s21_isnan(double x);

// long double factorial(int n);
long double s21_trunc(double x);
long double count_cos (long double ld_x);

#endif  // SRC_S21_MATCH_H_