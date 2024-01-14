#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  // Проверка на некорректные аргументы или размеры матриц
  if (A == NULL || B == NULL || A->rows < 1 || B->rows < 1 || A->columns < 1 ||
      B->columns < 1) {
    error = 1;
  } else if (A->columns != B->columns || A->rows != B->rows)
    error = 2;
  else {
    // Создание матрицы result с такими же размерами, как у A и B
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      // Вычитание элементов матрицы B из элементов матрицы A и сохранение
      // результата в result
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return error;  // Возвращаем код ошибки (0 - успех, 1 - некорректные данные, 2
                 // - матрицы разных размеров)
}