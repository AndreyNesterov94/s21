#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_nan(s21_tan(S21_INF));
  ck_assert_ldouble_nan(s21_tan(S21_N_INF));
  ck_assert_ldouble_nan(s21_tan(S21_NAN));
}
END_TEST

START_TEST(test_2) {
  for (double i = -10 * S21_PI; i < 10 * S21_PI; i += 3 * S21_PI / 7) {
    ck_assert_ldouble_lt(s21_fabs(s21_tan(i) - tan(i)), 1e-6);
  }
}
END_TEST

START_TEST(test_3) {
  ck_assert_ldouble_lt(s21_fabs(s21_tan(1000000) - tan(1000000)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_tan(-5000000) - tan(-5000000)), 1e-6);
}
END_TEST



Suite* make_s21_tan_suite(void) {
  Suite* s = suite_create("tan");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
