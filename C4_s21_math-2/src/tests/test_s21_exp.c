#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_infinite(s21_exp(S21_INF));
  ck_assert_ldouble_infinite(exp(S21_INF));

  ck_assert_ldouble_nan(s21_exp(S21_NAN));
  ck_assert_ldouble_nan(exp(S21_NAN));

  ck_assert_ldouble_eq(s21_exp(0), exp(0));
  ck_assert_ldouble_eq(s21_exp(S21_N_INF), exp(S21_N_INF));
}
END_TEST

START_TEST(test_2) {
  for (double i = 0.6495 * (-20); i < 0.6495 * 20; i += 0.6495) {
    ck_assert_ldouble_le(s21_fabs(s21_exp(i) - exp(i)), 1e-6);
  }
}
END_TEST

Suite* make_s21_exp_suite(void) {
  Suite* s = suite_create("exp");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);

  suite_add_tcase(s, tc);
  return s;
}
