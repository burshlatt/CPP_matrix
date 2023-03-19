#include "s21_matrix_oop.h"

// Метод доступа к атрибуту rows_ (accessor)
int S21Matrix::get_rows() const noexcept { return rows_; }

// Метод доступа к атрибуту cols_ (accessor)
int S21Matrix::get_cols() const noexcept { return cols_; }

// Метод изменения атрибута rows_ (mutator)
void S21Matrix::set_rows(const int rows) {
  if (rows <= 0) {
    throw std::out_of_range("Value can't be less or equal to 0");
  } else if (rows != rows_) {
    S21Matrix new_matrix(rows, cols_);
    const int rows_buff = (rows > rows_ ? rows_ : new_matrix.rows_);
    for (int i = 0; i < rows_buff; i++) {
      for (int j = 0; j < cols_; j++) {
        new_matrix(i, j) = matrix_[i][j];
      }
    }
    this->~S21Matrix();
    CreateMatrix(new_matrix.rows_, new_matrix.cols_);
    *this = new_matrix;
  }
}

// Метод изменения атрибута cols_ (mutator)
void S21Matrix::set_cols(const int cols) {
  if (cols <= 0) {
    throw std::out_of_range("Value can't be less or equal to 0");
  } else if (cols != cols_) {
    S21Matrix new_matrix(rows_, cols);
    const int cols_buff = (cols > cols_ ? cols_ : new_matrix.cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_buff; j++) {
        new_matrix(i, j) = matrix_[i][j];
      }
    }
    this->~S21Matrix();
    CreateMatrix(new_matrix.rows_, new_matrix.cols_);
    *this = new_matrix;
  }
}
