#include "tests.h"
#include "./../s21_math.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  Suite *s_fabs = make_s21_fabs_suite();
  Suite *s_abs = make_s21_abs_suite();
  Suite *s_cos = make_s21_cos_suite();
  Suite *s_floor = make_s21_floor_suite();
  Suite *s_ceil = make_s21_ceil_suite();
  Suite *s_fmod = make_s21_fmod_suite();
  Suite *s_exp = make_s21_exp_suite();
  Suite *s_log = make_s21_log_suite();
  Suite *s_atan = make_s21_atan_suite();
  Suite *s_asin = make_s21_asin_suite();
  Suite *s_acos = make_s21_acos_suite();
  Suite *s_sin = make_s21_sin_suite();
  Suite *s_tan = make_s21_tan_suite();
  Suite *s_pow = make_s21_pow_suite();
  Suite *s_sqrt = make_s21_sqrt_suite();

  SRunner *runner = srunner_create(s_fabs);
  srunner_add_suite(runner, s_abs);  
  srunner_add_suite(runner, s_cos);  
  srunner_add_suite(runner, s_floor);  
  srunner_add_suite(runner, s_ceil);  
  srunner_add_suite(runner, s_fmod);  
  srunner_add_suite(runner, s_exp);  
  srunner_add_suite(runner, s_log);  
  srunner_add_suite(runner, s_atan);  
  srunner_add_suite(runner, s_asin);  
  srunner_add_suite(runner, s_acos);  
  srunner_add_suite(runner, s_sin);
  srunner_add_suite(runner, s_tan);
  srunner_add_suite(runner, s_pow);
  srunner_add_suite(runner, s_sqrt);


  // printf("mat: %lf\n", pow(S21_NAN, 0));
  // printf("mat: %lf\n", pow(1, S21_NAN));
  // printf("mat: %Lf\n", s21_pow(S21_NAN, 0));
  // printf("mat: %Lf\n", s21_pow(1.0, S21_NAN));


  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
