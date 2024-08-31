#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  memset(result, 0, sizeof(matrix_t));
  int code = OK;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++) result->matrix[i][j] = 0;
  } else {
    code = INCORRECT_MATRIX;
  }
  return code;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int check_m(int rows, int columns, matrix_t *A) {
  return A == NULL           ? INCORRECT_MATRIX
         : A->matrix == NULL ? INCORRECT_MATRIX
         : (A->rows != rows || A->rows < 1) ||
                 (A->columns != columns || A->columns < 1)
             ? CALCULATION_ERROR
             : 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS, rows = A->rows, cols = A->columns;

  if (check_m(rows, cols, A) || check_m(rows, cols, B)) {
    flag = FAILURE;
  }

  if (flag == SUCCESS) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          flag = FAILURE;
          break;
        }
      }
      if (flag == FAILURE) break;
    }
  }

  return flag;
}
int sum_and_sub(matrix_t *A, matrix_t *B, matrix_t *result, char op) {
  memset(result, 0, sizeof(matrix_t));
  int code = 0, rows = A->rows, columns = A->columns;
  if (check_m(rows, columns, A)) {
    code = check_m(rows, columns, A);
  } else if (check_m(rows, columns, B)) {
    code = check_m(rows, columns, B);
  } else if (check_m(rows, columns, result)) {
    code = s21_create_matrix(rows, columns, result);
  }

  if (!code) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        switch (op) {
          case '+':
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            break;
          case '-':
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            break;
          default:
            break;
        }
      }
    }
  }

  return code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_and_sub(A, B, result, '+');
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_and_sub(A, B, result, '-');
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  memset(result, 0, sizeof(matrix_t));
  int code = OK, rows = A->rows, columns = A->columns;
  code = check_m(rows, columns, A);
  if (!code) {
    s21_create_matrix(rows, columns, result);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
  }

  return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  memset(result, 0, sizeof(matrix_t));
  int code = OK, rowsA = A->rows, columnsA = A->columns, rowsB = B->rows,
      columnsB = B->columns;
  code = check_m(rowsA, columnsA, A) || check_m(rowsB, columnsB, B);
  (columnsA != rowsB) &&!code ? code = CALCULATION_ERROR : 0;
  if (!code) {
    s21_create_matrix(rowsA, columnsB, result);
    for (int i = 0; i < A->rows && code == OK; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int l = 0; l < A->columns; l++) {
          result->matrix[i][j] += A->matrix[i][l] * B->matrix[l][j];
        }
      }
    }
  }
  return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  memset(result, 0, sizeof(matrix_t));
  int code = 0, rows = A->rows, columns = A->columns;
  code = check_m(rows, columns, A);
  if (!code) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  memset(result, 0, sizeof(matrix_t));
  int code = check_m(A->rows, A->columns, A);
  if (!code) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->rows, A->rows, result);
      if (A->rows == 1) {
        result->matrix[0][0] = 1;
      } else {
        fill_matrix_minors(A, result);
      }
    } else {
      code = CALCULATION_ERROR;
    }
  }
  return code;
}

void create_matrix_minor(matrix_t *A, int row, int column, matrix_t *result) {
  memset(result, 0, sizeof(matrix_t));
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  int new_matrix_i = 0;
  int new_matrix_j = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != row) {
      new_matrix_j = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != column) {
          result->matrix[new_matrix_i][new_matrix_j] = A->matrix[i][j];
          new_matrix_j++;
        }
      }
      new_matrix_i++;
    }
  }
}

void fill_matrix_minors(matrix_t *A, matrix_t *result) {
  if (A->rows == 1) {
    s21_determinant(A, &result->matrix[0][0]);
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t temp_matrix_minor;
        create_matrix_minor(A, i, j, &temp_matrix_minor);
        double tmp = 0;
        s21_determinant(&temp_matrix_minor, &tmp);
        result->matrix[i][j] = pow(-1, i + j) * tmp;
        s21_remove_matrix(&temp_matrix_minor);
      }
    }
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int code = check_m(A->rows, A->columns, A);
  if (!code) {
    if (A->rows == A->columns) {
      *result = det(A->matrix, A->rows);
    } else {
      code = CALCULATION_ERROR;
    }
  }
  return code;
}

void new_pointer(double **a, double *b) { *a = b; }

double det(double **a, int n) {
  double sum = 0;
  int f = 0;
  if (n == 1) {
    sum = a[0][0];
    f = 1;
  }
  if (n == 2) {
    sum = a[0][0] * a[1][1] - a[0][1] * a[1][0];
    f = 1;
  }
  if (f != 1) {
    int number = 0;
    double **temp = calloc((n - 1), sizeof(double *));
    for (int i = 0; i < n; i++) {
      number = 0;
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        new_pointer(&temp[number++], a[j]);
      }
      sum += pow(-1, i + n - 1) * a[i][n - 1] * det(temp, n - 1);
    }
    free(temp);
  }
  return sum;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  memset(result, 0, sizeof(matrix_t));
  int code = check_m(A->rows, A->columns, A);
  if (!code) {
    if (A->rows == A->columns) {
      double det = 0;
      s21_determinant(A, &det);
      if (fabs(det - 0) > EPS) {
        matrix_t algebraic_additions, transposed_algebraic_additions;
        s21_calc_complements(A, &algebraic_additions);
        s21_transpose(&algebraic_additions, &transposed_algebraic_additions);
        s21_mult_number(&transposed_algebraic_additions, 1 / det, result);
        s21_remove_matrix(&algebraic_additions);
        s21_remove_matrix(&transposed_algebraic_additions);
      } else {
        code = 2;
      }
    } else {
      code = 2;
    }
  }
  return code;
}
