#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 0;  // Переменная для хранения результата

  // Проверка на NaN значения
  if (s21_isnan(base) || s21_isnan(exp)) {
    if (exp == 0 || base == 1) {
      result = 1.0;  // Результат 1, если exp равен 0 или base равен 1
    } else {
      result = S21_NAN;  // Иначе результат равен NaN
    }
  } else if (base == 0 && exp < 0) {
    result = S21_INF;  // Результат равен бесконечности, если base равен 0 и exp меньше 0
  } else if (exp == 0) {
    result = 1.0;  // Результат равен 1, если exp равен 0
  } else {
    // Обработка случаев, когда exp не является целым числом
    if (exp != (long)exp) {
      if (base < 0) {
        result = S21_NAN;  // Результат NaN, если base отрицательное
      } else {
        result = s21_exp(exp * s21_log(s21_fabs(base)));  // Иначе вычисление степени
      }
    } else {
      // Обработка случаев, когда exp является целым числом
      long exp_int = (long)exp;
      if (exp_int < 0) {
        base = 1.0 / base;  // Если exp отрицательное, inverting base и сделать exp положительным
        exp_int = -exp_int;
      }
      result = 1.0;  // Инициализация результата
      for (long i = 0; i < exp_int; i++) {
        result *= base;  // Возведение в степень путем умножения
      }
    }

    // При необходимости сменить знак результата
    if (base < 0 && (long)((long long)exp) % 2 != 0) {
      result = -result;
    }
  }

  return result;  // Возврат результата
}
