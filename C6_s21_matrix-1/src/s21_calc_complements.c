#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  // Проверка на сущевствование или некорректные размеры матрицы A
  if (A == NULL || A->rows < 1 || A->columns < 1)
    error = 1;
  else {
    // Создаем матрицу для алгебраических дополнений
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        matrix_t matrix_minor;
        s21_smol_mat(i, j, A, &matrix_minor);  // Вычисляем минор матрицы
        double det_num = 0.0;
        // Вычисляем определитель минора
        s21_determinant(&matrix_minor, &det_num);
        // Вычисляем алгебраическое дополнение
        result->matrix[i][j] = pow((-1), i + j) * det_num;
        s21_remove_matrix(&matrix_minor);  // Удаляем временный минор
      }
    }
  }
  return error;  // Возвращаем код ошибки (0 - успех, 1 - некорректные
                 // аргументы)
}