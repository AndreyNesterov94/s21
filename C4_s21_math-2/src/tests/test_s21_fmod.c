#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, 20));
  ck_assert_ldouble_nan(s21_fmod(20, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(S21_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, S21_INF));
  ck_assert_ldouble_nan(s21_fmod(S21_INF, 3543.43));
  ck_assert_ldouble_nan(s21_fmod(20, 0));

  ck_assert_ldouble_nan(fmod(S21_NAN, 20));
  ck_assert_ldouble_nan(fmod(20, S21_NAN));
  ck_assert_ldouble_nan(fmod(S21_NAN, S21_NAN));
  ck_assert_ldouble_nan(fmod(S21_INF, S21_NAN));
  ck_assert_ldouble_nan(fmod(S21_NAN, S21_INF));
  ck_assert_ldouble_nan(fmod(S21_INF, 3543.43));
  ck_assert_ldouble_nan(fmod(20, 0));
}
END_TEST

START_TEST(test_2) {
  for (double i = 4.4213 * -15; i < 4.4213 * 15; i += 4.4213) {
    for (double j = 1.9032 * -20; j < 1.9032 * 20; j += 1.9031) {
      ck_assert_ldouble_lt(s21_fabs(s21_fmod(i, j) - fmod(i, j)), 1e-6);
    }
  }
}
END_TEST

START_TEST(test_3){
  ck_assert_ldouble_lt(s21_fabs(s21_fmod(5, S21_INF) - fmod(5, S21_INF)), 1e-6);

}

Suite* make_s21_fmod_suite(void) {
  Suite* s = suite_create("fmod");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
