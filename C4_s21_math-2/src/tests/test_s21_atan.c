#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_lt(s21_fabs(s21_atan(S21_INF) - atan(S21_INF)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_atan(S21_N_INF) - atan(S21_N_INF)), 1e-6);
  ck_assert_ldouble_nan(s21_atan(S21_NAN));
  ck_assert_ldouble_nan(atan(S21_NAN));
}
END_TEST

START_TEST(test_2) {
  ck_assert_ldouble_lt(s21_fabs(s21_atan(1) - atan(1)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_atan(-1) - atan(-1)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_atan(0) - atan(0)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_atan(42342.6532) - atan(42342.6532)), 1e-6);
}
END_TEST

START_TEST(test_3) {
  for (double i = 0.0273 * (-20); i < 0.0273 * 20; i += 0.0273) {
    ck_assert_ldouble_lt(s21_fabs(s21_atan(i) - atan(i)), 1e-6);
  }
  for (double i = 17.6332 * (-20); i < 17.6332 * 20; i += 17.6332) {
    ck_assert_ldouble_lt(s21_fabs(s21_atan(i) - atan(i)), 1e-6);
  }
}
END_TEST

Suite* make_s21_atan_suite(void) {
  Suite* s = suite_create("atan");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
