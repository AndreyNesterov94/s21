#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  // Проверка на существование или размеры матриц
  if (A == NULL || B == NULL || A->rows < 1 || B->rows < 1 || A->columns < 1 ||
      B->columns < 1)
    result = FAILURE;
  // Проверка на несовпадение размеров матриц
  else if (A->columns != B->columns || A->rows != B->rows)
    result = FAILURE;
  else {
    // Сравнение значений элементов матриц с заданной точностью (1е-7)
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = FAILURE;
          break;
        }
      }
    }
  }
  return result;
}