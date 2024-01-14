#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_nan(s21_acos(S21_NAN));
  ck_assert_ldouble_nan(s21_acos(S21_INF));
  ck_assert_ldouble_nan(s21_acos(S21_N_INF));
  ck_assert_ldouble_nan(s21_acos(-21));
  ck_assert_ldouble_nan(s21_acos(21));

  ck_assert_ldouble_nan(acos(S21_NAN));
  ck_assert_ldouble_nan(acos(S21_INF));
  ck_assert_ldouble_nan(acos(S21_N_INF));
  ck_assert_ldouble_nan(acos(-21));
  ck_assert_ldouble_nan(acos(21));
}
END_TEST

START_TEST(test_2) {
  ck_assert_ldouble_lt(s21_fabs(s21_acos(1) - acos(1)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_acos(-1) - acos(-1)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_acos(0) - acos(0)), 1e-6);
}
END_TEST

START_TEST(test_3) {
  for (double i = -1; i <= 1; i += 1.0/33) {
    ck_assert_ldouble_lt(s21_fabs(s21_acos(i) - acos(i)), 1e-6);
  }
}
END_TEST

Suite* make_s21_acos_suite(void) {
  Suite* s = suite_create("acos");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
