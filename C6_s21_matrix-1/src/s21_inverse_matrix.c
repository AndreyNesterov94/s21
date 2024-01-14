#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  double r;
  // Проверка на сущевствование или некорректные размеры матрицы A
  if (A == NULL || A->rows < 1 || A->columns < 1)
    error = 1;
  else if (A->rows != A->columns)
    error = 2;
  else if (!s21_determinant(A, &r) && !r)
    error = 2;
  else {
    matrix_t transpose, compl ;
    // Вычисляем алгебраические дополнения матрицы A и сохраняем их в
    // complements
    s21_calc_complements(A, &compl );
    // Вычисляем транспонированную матрицу complements и сохраняем ее в
    // transpose
    s21_transpose(&compl, &transpose);
    // Создаем матрицу result для хранения обратной матрицы
    s21_create_matrix(A->columns, A->rows, result);
    // Заполняем каждый элемент result делением соответствующего элемента из
    // transpose на определитель r
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = 1 / r * transpose.matrix[i][j];
    }
    // Удаляем временные матрицы transpose и complements
    s21_remove_matrix(&transpose);
    s21_remove_matrix(&compl );
  }

  return error;  // Возвращаем код ошибки (0 - успех, 1 - некорректные
                 // аргументы, 2 - обратная матрица не существует)
}