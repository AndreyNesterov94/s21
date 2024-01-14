#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_nan(s21_log(S21_NAN));
  ck_assert_ldouble_nan(s21_log(S21_N_INF));
  ck_assert_ldouble_nan(s21_log(-543.634));
  ck_assert_ldouble_infinite(s21_log(S21_INF));
  ck_assert_ldouble_infinite(-s21_log(0));

  ck_assert_ldouble_nan(log(S21_NAN));
  ck_assert_ldouble_nan(log(S21_N_INF));
  ck_assert_ldouble_nan(log(-543.634));
  ck_assert_ldouble_infinite(log(S21_INF));
  ck_assert_ldouble_infinite(-log(0));
}
END_TEST

START_TEST(test_2) {
  for (double i = 0.0001; i < 20; i += 0.39276) {
    ck_assert_ldouble_lt(s21_fabs(s21_log(i) - log(i)), 1e-6);
  }
  ck_assert_ldouble_lt(s21_fabs(s21_log(10000) - log(10000)), 1e-6);
}
END_TEST

Suite* make_s21_log_suite(void) {
  Suite* s = suite_create("log");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);

  suite_add_tcase(s, tc);
  return s;
}
