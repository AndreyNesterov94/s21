#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  // Проверка на существование или размеры матрицы A
  if (A == NULL || A->rows < 1 || A->columns < 1)
    error = 1;
  else {
    // Создание матрицы result с такими же размерами, как у A
    s21_create_matrix(A->rows, A->columns, result);
    // Умножение каждого элемента матрицы A на number и сохранение результата в
    // result
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;  // Возвращаем код ошибки (0 - успех, 1 - некорректные данные)
}