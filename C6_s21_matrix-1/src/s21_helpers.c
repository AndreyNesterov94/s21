#include "s21_matrix.h"

void s21_smol_mat(int n, int c, matrix_t *A, matrix_t *smat) {
  s21_create_matrix(A->rows - 1, A->columns - 1, smat);
  int i_n = 0;
  for (int i = 0; i < A->rows; i++) {
    int j_n = 0;
    if (i == n) continue;
    for (int j = 0; j < A->columns; j++) {
      if (j != c) {
        smat->matrix[i_n][j_n] = A->matrix[i][j];
        j_n++;
      }
    }
    i_n++;
  }
}

double s21_recursive_determinant(int n, matrix_t *A) {
  // Создаем временную матрицу new_matrix с уменьшенными размерами
  matrix_t new_matrix;
  s21_create_matrix(A->rows - 1, A->columns - 1, &new_matrix);
  double result = 0;

  // Если размер матрицы A равен 2x2, вычисляем определитель непосредственно
  if (n == 2) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    // Рекурсивно вычисляем определитель для матрицы размером больше 2x2
    for (int i = 0; i < n; i++) {
      int numj = 0;
      for (int j = 1; j < n; j++) {
        int numk = 0;
        for (int k = 0; k < n; k++) {
          if (k != i) {
            // Создаем минор матрицы A
            new_matrix.matrix[numj][numk] = A->matrix[j][k];
            numk++;
          }
        }
        numj++;
      }
      // Добавляем результат рекурсивного вызова с учетом знака и элемента A
      result += pow(-1, i) * A->matrix[0][i] *
                s21_recursive_determinant(n - 1, &new_matrix);
    }
  }
  // Удаляем временную матрицу
  s21_remove_matrix(&new_matrix);

  return result;
}
