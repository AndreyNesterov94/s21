#include "tests.h"

START_TEST(test_1) {
  ck_assert_ldouble_eq(s21_floor(9834.34544322), floor(9834.34544322));
  ck_assert_ldouble_eq(s21_floor(300000000.1), floor(300000000.1));
}
END_TEST

START_TEST(test_2) {
  ck_assert_ldouble_eq(s21_floor(-4252.9345), floor(-4252.9345));
}
END_TEST

START_TEST(test_3) {
  ck_assert_ldouble_nan(s21_floor(S21_NAN));
  ck_assert_ldouble_nan(floor(S21_NAN));

  ck_assert_ldouble_infinite(s21_floor(S21_INF));
  ck_assert_ldouble_infinite(-s21_floor(S21_N_INF));
  ck_assert_ldouble_infinite(floor(S21_INF));
  ck_assert_ldouble_infinite(-floor(S21_N_INF));
}
END_TEST

Suite* make_s21_floor_suite(void) {
  Suite* s = suite_create("floor");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
