#include "unit_tests.h"
#define CK_FORK no

START_TEST(test_s21_strchr_test1) {
  const char* str = "Privet, Anna!";
  const char* str1 = "Privet, Anna!";

  int c = 'a';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str1, c);

  ck_assert_pstr_eq(result, expected);
}

START_TEST(test_s21_strchr_test_2) {
  const char* str = "Privet, Anna!";
    const char* str1 = "Privet, Anna!";

  int c = 'x';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str1, c);

  ck_assert_pstr_eq(result, expected);
}

START_TEST(test_s21_strchr_test_3) {
  const char* str = "";
  const char* str1 = "";
  int c = 'x';

  char* result = s21_strchr(str, c);
  char* expected = strchr(str1, c);

  ck_assert_pstr_eq(result, expected);
}

Suite* make_s21_strchr_suite(void) {
  Suite* s = suite_create("s21_strchr");
  TCase* tc = tcase_create("s21_strchr");

  tcase_add_test(tc, test_s21_strchr_test1);
  tcase_add_test(tc, test_s21_strchr_test_2);
  tcase_add_test(tc, test_s21_strchr_test_3);

  suite_add_tcase(s, tc);
  return s;
}
