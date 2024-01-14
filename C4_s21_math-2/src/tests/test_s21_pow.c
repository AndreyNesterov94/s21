#include "tests.h"

#define CK_FORK no

START_TEST(test_1) {
  ck_assert_ldouble_lt(s21_fabs(s21_pow(2.0, 3.0) - 8.0), 1e-6);
}
END_TEST

START_TEST(test_2) {
  // Тест для отрицательных показателей степени
  ck_assert_ldouble_lt(s21_fabs(s21_pow(2.0, -3.0) - 0.125), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_pow(0.5, -2.0) - 4.0), 1e-6);
}
END_TEST

START_TEST(test_3) {
  // Тест для нулевого основания
  ck_assert_ldouble_eq(s21_pow(0.0, 0.0), 1.0);  // Любое число в степени 0 равно 1
  ck_assert_ldouble_eq(s21_pow(0.0, 3.0), 0.0);  // Нуль в любой положительной степени равен 0
  ck_assert(isinf(s21_pow(0.0, -3.0)));          // Нуль в отрицательной степени равен бесконечности
}
END_TEST

START_TEST(test_4) {
  // Тест для положительных степеней
  ck_assert_ldouble_lt(s21_fabs(s21_pow(2.0, 2.0) - 4.0), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_pow(2.0, 4.0) - 16.0), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_pow(1.5, 3.0) - 3.375), 1e-6);
}
END_TEST

START_TEST(test_5) {
  // Тест для нулевой степени
  ck_assert_ldouble_eq(s21_pow(2.0, 0.0), 1.0);  // Любое число в степени 0 равно 1
  ck_assert_ldouble_eq(s21_pow(0.0, 0.0), 1.0);  // Ноль в степени 0 также равен 1
  ck_assert_ldouble_eq(s21_pow(0.0, -0.0), 1.0); // Ноль в степени -0 тоже равен 1
}
END_TEST

START_TEST(test_6) {
  // Тест для дробных степеней
  ck_assert_ldouble_lt(s21_fabs(s21_pow(2.0, 0.5) - pow(2.0, 0.5)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_pow(3.0, 0.3333333) - pow(3.0, 0.3333333 )), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_pow(10.0, 0.25) - pow(10.0, 0.25)), 1e-6);
}
END_TEST

START_TEST(test_7) {
  // Тест для S21_INF
  ck_assert(isinf(s21_pow(2.0, S21_INF)));
  ck_assert(isinf(s21_pow(S21_INF, 3.0)));
}
END_TEST

START_TEST(test_8) {
  // Тест для S21_NAN
  ck_assert(isnan(s21_pow(-2.0, -2.5)));
  ck_assert(isnan(s21_pow(S21_NAN, 3.0)));
}
END_TEST

START_TEST(test_9) {
  // Тест для отрицательных дробных степеней
  ck_assert_ldouble_lt(s21_fabs(s21_pow(2.0, -0.5) - pow(2.0, -0.5)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_pow(3.0, -0.3333333) - pow(3.0, -0.3333333)), 1e-6);
  ck_assert_ldouble_lt(s21_fabs(s21_pow(10.0, -0.25) - pow(10.0, -0.25)), 1e-6);
}
END_TEST


START_TEST(test_10) {

  // Проверяем, что s21_pow и pow возвращают одинаковый результат для S21_NAN
  ck_assert(isnan(s21_pow(S21_NAN, 3.0)) && isnan(pow(S21_NAN, 3.0)));
  ck_assert(isnan(s21_pow(2.0, S21_NAN)) && isnan(pow(2.0, S21_NAN)));
  ck_assert(isnan(s21_pow(S21_NAN, S21_NAN)) && isnan(pow(S21_NAN, S21_NAN)));
}
END_TEST

START_TEST(test_11) {
  // Проверяем, что s21_pow и pow возвращают одинаковое значение (включая NaN)
  ck_assert(s21_pow(1.00, S21_NAN) == pow(1.00, S21_NAN));
  ck_assert(s21_pow(S21_NAN, 0) == pow(S21_NAN, 0));
}
END_TEST

START_TEST(test_12) {
  // Проверяем, что s21_pow и pow возвращают одинаковое значение (включая NaN)
  ck_assert(s21_pow(-2.0, -2.0) == pow(-2.0, -2.0));
}
END_TEST

START_TEST(test_13) {
  // Проверяем, что s21_pow и pow возвращают одинаковое значение (включая NaN)
  ck_assert(isnan(s21_pow(-2.0, 3.3)) == isnan(pow(-2.0, 3.3)));
}
END_TEST









Suite* make_s21_pow_suite(void) {
  Suite* s = suite_create("pow");
  TCase* tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);


  suite_add_tcase(s, tc);
  return s;
}
