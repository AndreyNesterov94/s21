#include "unit_tests.h"

START_TEST(test_s21_trim_test_1) {
  const char* str = "aaababbabccabab Hello abbcacbbcbabbcab";
  char* result = s21_trim(str, "abc");

  // Ожидаем, что результат для пустой строки также будет пустым
  ck_assert_str_eq(result, " Hello ");

  free(result);
}

START_TEST(test_s21_trim_test_2) {
  const char* str = s21_NULL;
  char* result = s21_trim(str, s21_NULL);

  // Ожидаем, что результат для пустой строки также будет пустым
  ck_assert_pstr_eq(result, s21_NULL);

  free(result);
}

START_TEST(test_s21_trim_test_3) {
  const char* str = "Hello";
  char* result = s21_trim(str, s21_NULL);

  // Ожидаем, что результат для пустой строки также будет пустым
  ck_assert_pstr_eq(result, s21_NULL);

  free(result);
}

START_TEST(test_s21_trim_test_4) {
  const char* str = "Hello";
  char* result = s21_trim(str, "Hello");

  // Ожидаем, что результат для пустой строки также будет пустым
  ck_assert_pstr_eq(result, "");

  free(result);
}

Suite* make_s21_trim_suite(void) {
  Suite* s = suite_create("s21_trim");
  TCase* tc = tcase_create("s21_trim");

  tcase_add_test(tc, test_s21_trim_test_1);
  tcase_add_test(tc, test_s21_trim_test_2);
  tcase_add_test(tc, test_s21_trim_test_3);
  tcase_add_test(tc, test_s21_trim_test_4);
  // tcase_add_test(tc, test_s21_trim_test_5);
  // tcase_add_test(tc, test_s21_trim_test_6);

  suite_add_tcase(s, tc);
  return s;
}
