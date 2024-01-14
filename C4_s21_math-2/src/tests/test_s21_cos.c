#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_nan(s21_cos(S21_INF));
  ck_assert_ldouble_nan(s21_cos(S21_N_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
}
END_TEST

START_TEST(test_2) {
  for (double i = -10 * S21_PI; i < 10 * S21_PI; i += 3 * S21_PI / 7) {
    ck_assert_ldouble_lt(s21_fabs(s21_cos(i) - cos(i)), 1e-6);
  }
}
END_TEST

START_TEST(test_3) {
  ck_assert_ldouble_lt(s21_fabs(s21_cos(1000000) - cos(1000000)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_cos(-5000000) - cos(-5000000)), 1e-6);
}
END_TEST

START_TEST(test_4) {
  ck_assert_ldouble_lt(s21_fabs(s21_cos(S21_PI) - cos(S21_PI)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_cos(S21_PI / 2) - cos(S21_PI /2)), 1e-6);
}
END_TEST

Suite* make_s21_cos_suite(void) {
  Suite* s = suite_create("cos");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);

  suite_add_tcase(s, tc);
  return s;
}
