#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows < 1 || columns < 1 || result == NULL) {
    error = 1;  // Недопустимые размеры или нулевой указатель
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      error = 1;  // Не удалось выделить память
    } else {
      for (int i = 0; i < rows && !error; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          error = 1;  // Не удалось выделить память
          // Освобождаем ранее выделенную память
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          result->matrix = NULL;
        }
      }
    }
  }
  return error;
}
