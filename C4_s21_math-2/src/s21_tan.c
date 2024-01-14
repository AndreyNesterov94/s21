#include "s21_math.h"

long double s21_tan(double x){
    long double tan;
    if (x != x || x == S21_INF || x == S21_N_INF){
        tan = S21_NAN;
    }
    else{
        long double cos = s21_cos(x);
        tan = s21_sin(x)/cos;
    }
    return tan;
}