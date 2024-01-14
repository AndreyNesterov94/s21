#include "s21_math.h"

long double s21_sin(double x){
    long double sin;
    if (x != x || x == S21_INF || x == S21_N_INF){
        sin = S21_NAN;
    }
    else
    { 
        int isNegative1 = 0, isNegative2 = 0;
        if (x < 0) isNegative1 = 1;
        long double ld_x = s21_fmod(x, 2 * S21_PI);
        if (ld_x < 0) ld_x = -ld_x;
        
        if ( ld_x > S21_PI && ld_x < 2 * S21_PI){
            isNegative2 = 1;
        }
        if (s21_fabs(ld_x) < 1e-7 || s21_fabs(ld_x - S21_PI)  < 1e-7) sin = 0;
        else if (ld_x == S21_PI / 2 || ld_x == 3 * S21_PI / 2) sin = 1;
        else  {
            sin = s21_sqrt(1 - (s21_cos(ld_x) * s21_cos(ld_x)));
            }
        if(isNegative1) sin = -sin;
        if(isNegative2) sin = -sin;
        
    }
    return sin;
}


 
