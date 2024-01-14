#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_lt(s21_fabs(s21_sqrt(4.0) - 2.0), 1e-12);
}
END_TEST

START_TEST(test_2) {
  for (double x = 0.1; x <= 10.0; x += 0.1) {
    double result = s21_sqrt(x);
    double expected_result = sqrt(x);
    ck_assert_ldouble_lt(s21_fabs(result - expected_result), 1e-6);
  }
}
END_TEST

START_TEST(test_3) {
  ck_assert_ldouble_eq(s21_sqrt(0.0), 0.0);
}
END_TEST

START_TEST(test_4) {
  ck_assert_ldouble_nan(s21_sqrt(-1));
  ck_assert_ldouble_nan(s21_sqrt(S21_NAN));
}
END_TEST

Suite* make_s21_sqrt_suite(void) {
  Suite* s = suite_create("sqrt");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);

  suite_add_tcase(s, tc);
  return s;
}
