#include "tests.h"

START_TEST(test_1) {
  ck_assert_ldouble_eq(s21_ceil(9834.34542), ceil(9834.34542));
}
END_TEST

START_TEST(test_2) {
  ck_assert_ldouble_eq(s21_ceil(-4252.9345), ceil(-4252.9345));
}
END_TEST

START_TEST(test_3) {
  ck_assert_ldouble_nan(s21_ceil(S21_NAN));
  ck_assert_ldouble_nan(ceil(S21_NAN));

  ck_assert_ldouble_infinite(s21_ceil(S21_INF));
  ck_assert_ldouble_infinite(-s21_ceil(S21_N_INF));
  ck_assert_ldouble_infinite(ceil(S21_INF));
  ck_assert_ldouble_infinite(-ceil(S21_N_INF));
}
END_TEST

Suite* make_s21_ceil_suite(void) {
  Suite* s = suite_create("ceil");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
