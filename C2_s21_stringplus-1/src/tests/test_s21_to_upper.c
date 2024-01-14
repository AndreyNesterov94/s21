#include "unit_tests.h"

START_TEST(test_s21_to_upper_test_1) {
    const char* str = "";
    char* result = s21_to_upper(str);
    
    // Ожидаем, что результат для пустой строки также будет пустым
    ck_assert_str_eq(result, "");

    free(result);
}

START_TEST(test_s21_to_upper_test_2) {
    const char* str = "hello";
    char* result = s21_to_upper(str);
    
    // Ожидаем, что все символы строки будут в верхнем регистре
    const char* expected = "HELLO";
    ck_assert_str_eq(result, expected);

    free(result);
}

START_TEST(test_s21_to_upper_test_3) {
    const char* str = "WORLD";
    char* result = s21_to_upper(str);
    
    // Если строка уже в верхнем регистре, результат должен быть таким же
    ck_assert_str_eq(result, str);

    free(result);
}

START_TEST(test_s21_to_upper_test_4) {
    const char* str = "HeLLo WoRLd";
    char* result = s21_to_upper(str);
    
    // Ожидаем, что все буквы в строке будут в верхнем регистре, а остальные символы останутся неизменными
    const char* expected = "HELLO WORLD";
    ck_assert_str_eq(result, expected);

    free(result);
}

START_TEST(test_s21_to_upper_test_5) {
    const char* str = "!@#$%^&*()";
    char* result = s21_to_upper(str);
    
    // Ожидаем, что специальные символы не изменятся
    ck_assert_str_eq(result, str);

    free(result);
}

Suite* make_s21_to_upper_suite(void) {
    Suite* s = suite_create("s21_to_upper");
    TCase* tc = tcase_create("s21_to_upper");

    tcase_add_test(tc, test_s21_to_upper_test_1);
    tcase_add_test(tc, test_s21_to_upper_test_2);
    tcase_add_test(tc, test_s21_to_upper_test_3);
    tcase_add_test(tc, test_s21_to_upper_test_4);
    tcase_add_test(tc, test_s21_to_upper_test_5);

    suite_add_tcase(s, tc);
    return s;
}
