#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_nan(s21_sin(S21_INF));
  ck_assert_ldouble_nan(s21_sin(S21_N_INF));
  ck_assert_ldouble_nan(s21_sin(S21_NAN));
}
END_TEST

START_TEST(test_2) {
  for (double i = -10 * S21_PI; i < 10 * S21_PI; i += 3 * S21_PI / 7) {
    ck_assert_ldouble_lt(s21_fabs(s21_sin(i) - sin(i)), 1e-6);
  }
}
END_TEST

START_TEST(test_3) {

  ck_assert_ldouble_lt(s21_fabs(s21_sin(1000000) - sin(1000000)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_sin(-5000000) - sin(-5000000)), 1e-6);
}
END_TEST



Suite* make_s21_sin_suite(void) {
  Suite* s = suite_create("sin");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
