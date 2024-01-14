#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  // Проверка на существование или некорректные размеры матрицы A
  if (A == NULL || A->rows < 1 || A->columns < 1)
    error = 1;
  else if (A->rows != A->columns)
    error = 2;
  else {
    if (A->rows == 1)
      *result = A->matrix[0][0];  // Определитель для 1x1 матрицы
    else
      *result = s21_recursive_determinant(
          A->rows, A);  // Вычисление определителя через рекурсивную функцию
  }
  return error;  // Возвращаем код ошибки (0 - успех, 1 - некорректные
                 // аргументы, 2 - не квадратная матрица)
}