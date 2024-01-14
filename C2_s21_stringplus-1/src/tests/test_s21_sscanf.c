#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_sscanf_test_1) {
  char str[] = "   321Let`s start";
  char c1;
  char c2;
  int i1;
  int i2;
  int cnt1 = s21_sscanf(str, "%c%d", &c1, &i1);
  int cnt2 = sscanf(str, "%c%d", &c2, &i2);

  ck_assert_int_eq(cnt1, cnt2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq((int)c1, (int)c2);
}
END_TEST

Suite* make_s21_sscanf_suite(void) {
  Suite* s = suite_create("s21_sscanf");
  TCase* tc = tcase_create("s21_sscanf");

  tcase_add_test(tc, test_s21_sscanf_test_1);

  suite_add_tcase(s, tc);
  return s;
}
