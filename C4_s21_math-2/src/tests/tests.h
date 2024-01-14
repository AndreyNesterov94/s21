#ifndef _UNI_TEST_H
#define _UNI_TEST_H
#include <check.h>

#include "../s21_math.h"
#include "math.h"

Suite* make_s21_fabs_suite(void);
Suite* make_s21_abs_suite(void);
Suite* make_s21_cos_suite(void);
Suite* make_s21_sin_suite(void);
Suite* make_s21_tan_suite(void);
Suite* make_s21_floor_suite(void);
Suite* make_s21_ceil_suite(void);
Suite* make_s21_fmod_suite(void);
Suite* make_s21_exp_suite(void);
Suite* make_s21_log_suite(void);
Suite* make_s21_atan_suite(void);
Suite* make_s21_asin_suite(void);
Suite* make_s21_acos_suite(void);
Suite* make_s21_pow_suite(void);
Suite* make_s21_sqrt_suite(void);

#endif
