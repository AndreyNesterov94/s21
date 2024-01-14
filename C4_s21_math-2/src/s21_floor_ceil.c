#include "s21_math.h"

long double s21_floor(double x) {
  long double res = 0;
  if (x != x || x == S21_INF || x == S21_N_INF) {
    res = x;
  } else {
    res = s21_trunc(x);
    if (x < 0) {
      res -= 1;
    }
  }
  return res;
}

long double s21_ceil(double x) {
  long double res = 0;
  if (x != x || x == S21_INF || x == S21_N_INF) {
    res = x;
  } else {
    res = s21_trunc(x);
    if (x > 0) {
      res += 1;
    }
  }
  return res;
}

//в дабле лежит формат sign exp m2 m1 где число равно 1.m2m1 * 2^(exp)
long double s21_trunc(double x) {
  long double res = 0;
  if (x <= -1 || x >= 1) {
    double_cast cast;
    cast.data = x;
      // UNCOMMENT TO SEE HOW IT WORKS

    // for (int i = 0; i < 32; i++) {
    //   printf("%d", (cast.bits.mantis1 >> (31 - i)) & 1);
    // }
    // printf("\n\n");
    // for (int i = 0; i < 20; i++) {
    //   printf("%d", (cast.bits.mantis2 >> (19 - i)) & 1);
    // }
    
    if (cast.bits.exponent - 1023 <= 20) {
    cast.bits.mantis2 = cast.bits.mantis2 >> (20 - (cast.bits.exponent - 1023));
    cast.bits.mantis2 = cast.bits.mantis2 << (20 - (cast.bits.exponent - 1023));
    cast.bits.mantis1 = 0;
    }
    else {
      cast.bits.mantis1 =
          cast.bits.mantis1 >> (32 - (cast.bits.exponent - 1023 - 20));
      cast.bits.mantis1 = cast.bits.mantis1
                          << (32 - (cast.bits.exponent - 1023 - 20));
    } 

    res = cast.data;
  }
  
  return res;
}