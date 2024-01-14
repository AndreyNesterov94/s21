#include "unit_tests.h"

START_TEST(test_s21_to_lower_test_1) {
  const char* str = "";
  char* result = s21_to_lower(str);

  ck_assert_str_eq(result, "");

  free(result);
}

START_TEST(test_s21_to_lower_test_2) {
  const char* str = "hello";
  char* result = s21_to_lower(str);

  // Если строка уже в нижнем регистре, результат должен быть таким же
  ck_assert_str_eq(result, str);

  free(result);
}

START_TEST(test_s21_to_lower_test_3) {
  const char* str = "WORLD";
  char* result = s21_to_lower(str);

  // Ожидаем, что все символы строки будут в нижнем регистре
  const char* expected = "world";
  ck_assert_str_eq(result, expected);

  free(result);
}

START_TEST(test_s21_to_lower_test_4) {
  const char* str = "HeLLo WoRLd";
  char* result = s21_to_lower(str);

  // Ожидаем, что все буквы в строке будут в нижнем регистре, а остальные
  // символы останутся неизменными
  const char* expected = "hello world";
  ck_assert_str_eq(result, expected);

  free(result);
}

START_TEST(test_s21_to_lower_test_5) {
  const char* str = "!@#$%^&*()";
  char* result = s21_to_lower(str);

  // Ожидаем, что специальные символы не изменятся
  ck_assert_str_eq(result, str);

  free(result);
}

START_TEST(test_s21_to_lower_test_6) {
  const char* str = s21_NULL;
  char* result = s21_to_lower(str);

  ck_assert_pstr_eq(result, s21_NULL);

  free(result);
}

Suite* make_s21_to_lower_suite(void) {
  Suite* s = suite_create("s21_to_lower");
  TCase* tc = tcase_create("s21_to_lower");

  tcase_add_test(tc, test_s21_to_lower_test_1);
  tcase_add_test(tc, test_s21_to_lower_test_2);
  tcase_add_test(tc, test_s21_to_lower_test_3);
  tcase_add_test(tc, test_s21_to_lower_test_4);
  tcase_add_test(tc, test_s21_to_lower_test_5);
  tcase_add_test(tc, test_s21_to_lower_test_6);

  suite_add_tcase(s, tc);
  return s;
}
