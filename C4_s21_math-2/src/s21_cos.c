#include "s21_math.h"

long double s21_cos(double x) {
  long double res;
  if (x != x || x == S21_INF || x == S21_N_INF) {
    res = S21_NAN;
  } else {
    long double ld_x = s21_fmod(x, 2 * S21_PI);
    if (ld_x < 0) ld_x = -ld_x;

    if (s21_fabs(ld_x) < 1e-8) {
      res = 1;
    } else if (s21_fabs(ld_x - S21_PI) < 1e-9) {
      res = -1;
    } else if (s21_fabs(ld_x - S21_PI / 2) < 1e-9 || s21_fabs(x - 3 * S21_PI / 2) < 1e-9) {
      res = 0;
    } else {
            res = count_cos (ld_x);	
    }
  }
  return res;
}

long double count_cos (long double ld_x){
    long double res = 1;
    long double last_res = 0, pow2 = 1, factorial = 1;
	int k = 2, n = -1;
    while (s21_fabs(res - last_res) >= 1e-6) {
        last_res = res;
        factorial *= k * (k - 1);
        pow2 *= ld_x * ld_x;
        res += n * pow2/factorial;
        k += 2;
        n *= -1;
    }
    return res;	
}

// long double factorial(int n) {
//   long double fac = 1;
//   if (n == 0 || n == 1) {
//     fac = 1;
//   } else {
//     for (int i = n; i > 0; i--) {
//       fac *= i;
//     }
//   }
//   return fac;
// }