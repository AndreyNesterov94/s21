#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_nan(s21_asin(S21_NAN));
  ck_assert_ldouble_nan(s21_asin(S21_INF));
  ck_assert_ldouble_nan(s21_asin(S21_N_INF));
  ck_assert_ldouble_nan(s21_asin(-21));
  ck_assert_ldouble_nan(s21_asin(21));

  ck_assert_ldouble_nan(asin(S21_NAN));
  ck_assert_ldouble_nan(asin(S21_INF));
  ck_assert_ldouble_nan(asin(S21_N_INF));
  ck_assert_ldouble_nan(asin(-21));
  ck_assert_ldouble_nan(asin(21));
}
END_TEST

START_TEST(test_2) {
  ck_assert_ldouble_lt(s21_fabs(s21_asin(1) - asin(1)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_asin(-1) - asin(-1)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_asin(0) - asin(0)), 1e-6);
}
END_TEST

START_TEST(test_3) {
  for (double i = -1; i <= 1; i += 1.0/33) {
    ck_assert_ldouble_lt(s21_fabs(s21_asin(i) - asin(i)), 1e-6);
  }
}
END_TEST

Suite* make_s21_asin_suite(void) {
  Suite* s = suite_create("asin");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
