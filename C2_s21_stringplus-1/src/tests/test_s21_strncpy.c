#include "unit_tests.h"
#include <string.h>

#define CK_FORK no

START_TEST(test_s21_strncpy_test_1) {
    char dest[20] = "Hello, ";
    char dest1[20] = "Hello, ";
    const char* src = "Wasya!";
    size_t n = 7;

    char* result = s21_strncpy(dest, src, n);
    char* expected = strncpy(dest1, src, n);

    ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strncpy_test_2) {
    char dest[20] = "Hello, ";
    char dest1[20] = "Hello, ";
    const char* src = "Wasya!";
    size_t n = 12;

    char* result = s21_strncpy(dest, src, n);
    char* expected = strncpy(dest1, src, n);

    ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strncpy_test_3) {
    char dest[20] = "Hello, ";
    char dest1[20] = "Hello, ";
    const char* src = "";
    size_t n = 7;

    char* result = s21_strncpy(dest, src, n);
    char* expected = strncpy(dest1, src, n);

    ck_assert_str_eq(result, expected);
}
END_TEST

Suite* make_s21_strncpy_suite(void) {
    Suite* s = suite_create("s21_strncpy");
    TCase* tc = tcase_create("s21_strncpy");

    tcase_add_test(tc, test_s21_strncpy_test_1);
    tcase_add_test(tc, test_s21_strncpy_test_2);
    tcase_add_test(tc, test_s21_strncpy_test_3);

    suite_add_tcase(s, tc);
    return s;
}
