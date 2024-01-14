#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strncat_test1) {
  s21_size_t n = 3;
  char str1[16] = "abc";
  char str2[16] = "qwe";
  char str3[16] = "qwe";
  s21_strncat(str2, str1, n);
  strncat(str3, str1, n);
  ck_assert_str_eq(str2, str3);
}
END_TEST

START_TEST(test_s21_strncat_test2) {
  s21_size_t n = 0;
  char str1[16] = "";
  char str2[16] = "qwe";
  char str3[16] = "qwe";
  s21_strncat(str2, str1, n);
  strncat(str3, str1, n);
  ck_assert_str_eq(str2, str3);
}
END_TEST

START_TEST(test_s21_strncat_test3) {
  s21_size_t n = 2;
  char str1[16] = "abc";
  char str2[16] = "";
  char str3[16] = "";
  s21_strncat(str2, str1, n);
  strncat(str3, str1, n);
  ck_assert_str_eq(str2, str3);
}
END_TEST

START_TEST(test_s21_strncat_test4) {
  s21_size_t n = 4;
  char str1[16] = "privet";
  char str2[16] = "komu";
  char str3[16] = "komu";
  s21_strncat(str2, str1, n);
  strncat(str3, str1, n);
  ck_assert_str_eq(str2, str3);
}
END_TEST

START_TEST(test_s21_strncat_test5) {
  s21_size_t n = 7;
  char str1[16] = "privet";
  char str2[16] = "k\0omy tebe";
  char str3[16] = "k\0my tebe";
  s21_strncat(str2, str1, n);
  strncat(str3, str1, n);
  ck_assert_str_eq(str2, str3);
}
END_TEST

START_TEST(test_s21_strncat_test6) {
  s21_size_t n = 0;
  char str1[16] = "";
  char str2[16] = "";
  char str3[16] = "";
  s21_strncat(str2, str1, n);
  strncat(str3, str1, n);
  ck_assert_str_eq(str2, str3);
}
END_TEST

START_TEST(test_s21_strncat_test7) {
  s21_size_t n = 5;
  char str1[16] = "pri\0vet";
  char str2[16] = "komu";
  char str3[16] = "komu";
  s21_strncat(str2, str1, n);
  strncat(str3, str1, n);
  ck_assert_str_eq(str2, str3);
}
END_TEST

Suite *suite_strncat(void) {
  Suite *s = suite_create("suite_strncat");
  TCase *tc = tcase_create("strncat_tc");

  tcase_add_test(tc, test_s21_strncat_test1);
  tcase_add_test(tc, test_s21_strncat_test2);
  tcase_add_test(tc, test_s21_strncat_test3);
  tcase_add_test(tc, test_s21_strncat_test4);
  tcase_add_test(tc, test_s21_strncat_test5);
  tcase_add_test(tc, test_s21_strncat_test6);
  tcase_add_test(tc, test_s21_strncat_test7);

  suite_add_tcase(s, tc);

  return s;
}
