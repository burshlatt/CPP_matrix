#include "s21_matrix_oop.h"

// Перегрузка оператора сложения двух матриц
S21Matrix S21Matrix::operator+(const S21Matrix& matrix) noexcept {
  S21Matrix result_matrix(*this);
  result_matrix.SumMatrix(matrix);
  return result_matrix;
}

// Перегрузка оператора вычитания двух матриц
S21Matrix S21Matrix::operator-(const S21Matrix& matrix) noexcept {
  S21Matrix result_matrix(*this);
  result_matrix.SubMatrix(matrix);
  return result_matrix;
}

// Перегрузка оператора умножения матриц
S21Matrix S21Matrix::operator*(const S21Matrix& matrix) noexcept {
  S21Matrix result_matrix(*this);
  result_matrix.MulMatrix(matrix);
  return result_matrix;
}

// Перегрузка оператора умножения матрицы на число (матрица * число)
S21Matrix operator*(S21Matrix& matrix, const double number) noexcept {
  S21Matrix result_matrix(matrix);
  result_matrix.MulNumber(number);
  return result_matrix;
}

// Перегрузка оператора умножения матрицы на число (число * матрица)
S21Matrix operator*(const double number, S21Matrix& matrix) noexcept {
  S21Matrix result_matrix(matrix);
  result_matrix.MulNumber(number);
  return result_matrix;
}

// Перегрузка оператора проверки на равенство
bool S21Matrix::operator==(const S21Matrix& matrix) const noexcept {
  return EqMatrix(matrix);
}

// Перегрузка оператора проверки на неравенство
bool S21Matrix::operator!=(const S21Matrix& matrix) const noexcept {
  bool result = true;
  if (EqMatrix(matrix)) {
    result = false;
  }
  return result;
}

// Перегрузка оператора присвоения-сложения
S21Matrix& S21Matrix::operator+=(const S21Matrix& matrix) noexcept {
  SumMatrix(matrix);
  return *this;
}

// Перегрузка оператора присвоение разности
S21Matrix& S21Matrix::operator-=(const S21Matrix& matrix) noexcept {
  SubMatrix(matrix);
  return *this;
}

// Перегрузка оператора присвоение умножения матрицы на матрицу
S21Matrix& S21Matrix::operator*=(const S21Matrix& matrix) noexcept {
  MulMatrix(matrix);
  return *this;
}

// Перегрузка оператора присвоение умножения матрицы на число
S21Matrix& S21Matrix::operator*=(const double number) noexcept {
  MulNumber(number);
  return *this;
}

// Перегрузка оператора присваивания матрице значений другой матрицы
S21Matrix& S21Matrix::operator=(const S21Matrix& matrix) noexcept {
  this->~S21Matrix();
  CreateMatrix(matrix.rows_, matrix.cols_);
  MoveMatrix(matrix);
  return *this;
}

// Перегрузка оператора индексации по элементам матрицы
double& S21Matrix::operator()(const int row, const int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("This element doesn't exist");
  }
  return matrix_[row][col];
}
