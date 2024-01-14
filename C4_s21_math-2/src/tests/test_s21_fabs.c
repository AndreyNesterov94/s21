#include "tests.h"

START_TEST(test_1) { ck_assert_ldouble_eq(s21_fabs(98.32), fabs(98.32)); }
END_TEST

START_TEST(test_2) { ck_assert_ldouble_eq(s21_fabs(-4), fabs(4.)); }
END_TEST

START_TEST(test_3) {
  ck_assert_ldouble_nan(s21_fabs(S21_NAN));
  ck_assert_ldouble_nan(fabs(S21_NAN));

  ck_assert_ldouble_infinite(s21_fabs(S21_INF));
  ck_assert_ldouble_infinite(s21_fabs(S21_N_INF));
  ck_assert_ldouble_infinite(fabs(S21_INF));
  ck_assert_ldouble_infinite(fabs(S21_N_INF));
}
END_TEST

Suite* make_s21_fabs_suite(void) {
  Suite* s = suite_create("fabs");
  TCase* tc = tcase_create("s21_fabs");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
