#include "s21_matrix_oop.h"

// Дополнительный метод создания матрицы
void S21Matrix::CreateMatrix(const int rows, const int cols) noexcept {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]{};
  }
}

// Дополнительный метод копирования матрицы
void S21Matrix::MoveMatrix(const S21Matrix &matrix) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix(i, j);
    }
  }
}

// Дополнительный метод сложения-вычитания
void S21Matrix::SubOrSum(const S21Matrix &matrix, const bool is_sum) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (is_sum == true) {
        matrix_[i][j] += matrix.matrix_[i][j];
      } else {
        matrix_[i][j] -= matrix.matrix_[i][j];
      }
    }
  }
}

// Дополнительный метод нахождения минора
void S21Matrix::MinorSearch(double **A, double **buffer, int skip_i, int skip_j,
                            int size) const noexcept {
  int index_i = 0;
  int index_j = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i != skip_i && j != skip_j) {
        buffer[index_i][index_j++] = A[i][j];
        if (index_j == size - 1) {
          index_j = 0;
          index_i++;
        }
      }
    }
  }
}

// Дополнительный метод нахождения детерминанта
double S21Matrix::DeterminantSearch(S21Matrix *A, int size) const noexcept {
  double result = 0.0;
  if (size == 1) {
    result = A->matrix_[0][0];
  } else {
    S21Matrix *buffer = new S21Matrix(size, size);
    for (int i = 0; i < size; i++) {
      MinorSearch(A->matrix_, buffer->matrix_, 0, i, size);
      if (i % 2 == 0) {
        result += A->matrix_[0][i] * DeterminantSearch(buffer, size - 1);
      } else {
        result -= A->matrix_[0][i] * DeterminantSearch(buffer, size - 1);
      }
    }
    delete buffer;
  }
  return result;
}
