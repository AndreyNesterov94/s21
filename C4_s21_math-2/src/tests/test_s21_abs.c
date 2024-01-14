#include "tests.h"
#define CK_FORK no

START_TEST(test_1) { ck_assert_int_eq(s21_abs(98), abs(98)); }
END_TEST

START_TEST(test_2) { ck_assert_int_eq(s21_abs(-65), abs(-65)); }
END_TEST

START_TEST(test_3) { ck_assert_int_eq(s21_abs(0), abs(0)); }
END_TEST

Suite* make_s21_abs_suite(void) {
  Suite* s = suite_create("abs");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
