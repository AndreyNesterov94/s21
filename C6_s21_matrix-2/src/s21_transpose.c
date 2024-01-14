#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  // Проверка на существование или размеры матрицы A
  if (A == NULL || A->rows < 1 || A->columns < 1)
    error = 1;
  else {
    // Создание матрицы result с размерами, перевернутыми относительно матрицы A
    s21_create_matrix(A->columns, A->rows, result);
    // Транспонирование: перенос элементов из матрицы A в result
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return error;  // Возвращаем код ошибки (0 - успех, 1 - некорректные данные)
}