#include "s21_matrix_oop.h"

// Дефолтный конструктор
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// Параметризированный конструктор с количеством строк и столбцов
S21Matrix::S21Matrix(const int rows, const int cols)
    : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols <= 0) {
    throw std::invalid_argument("Values can't be less or equal to 0");
  }
  CreateMatrix(rows, cols);
}

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& matrix) : rows_(matrix.rows_), cols_(matrix.cols_) {
  if (matrix.matrix_ == nullptr) {
    throw std::underflow_error("Matrix is empty");
  }
  CreateMatrix(matrix.rows_, matrix.cols_);
  MoveMatrix(matrix);
}

// Конструктор переноса
S21Matrix::S21Matrix(S21Matrix&& matrix) noexcept {
  rows_ = std::exchange(matrix.rows_, 0);
  cols_ = std::exchange(matrix.cols_, 0);
  matrix_ = std::exchange(matrix.matrix_, nullptr);
}

// Деструктор класса
S21Matrix::~S21Matrix() noexcept {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

// Метод сравнения матриц
bool S21Matrix::EqMatrix(const S21Matrix& matrix) const noexcept {
  bool status = true;
  if (rows_ == matrix.rows_ && cols_ == matrix.cols_) {
    for (int i = 0; i < rows_ && status == true; i++) {
      for (int j = 0; j < cols_ && status == true; j++) {
        double num_1 = matrix_[i][j];
        double num_2 = matrix.matrix_[i][j];
        if (std::fabs(num_1 - num_2) >=
            std::numeric_limits<double>::epsilon()) {
          status = false;
        }
      }
    }
  } else {
    status = false;
  }
  return status;
}

// Метод сложения матриц
void S21Matrix::SumMatrix(const S21Matrix& matrix) {
  if (rows_ != matrix.rows_ || cols_ != matrix.cols_) {
    throw std::out_of_range("Matrix must be the same size");
  }
  SubOrSum(matrix, true);
}

// Метод вычитания матриц
void S21Matrix::SubMatrix(const S21Matrix& matrix) {
  if (rows_ != matrix.rows_ || cols_ != matrix.cols_) {
    throw std::out_of_range("Matrix must be the same size");
  }
  SubOrSum(matrix, false);
}

// Метод умножения матрицы на число
void S21Matrix::MulNumber(const double number) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= number;
    }
  }
}

// Метод перемножения матриц
void S21Matrix::MulMatrix(const S21Matrix& matrix) {
  if (cols_ != matrix.rows_) {
    throw std::invalid_argument("The number of columns of matrix 1 must equal the number of rows of matrix 2");
  }
  S21Matrix matrix_result(rows_, matrix.cols_);
  for (int i = 0; i < matrix_result.rows_; i++) {
    for (int j = 0; j < matrix_result.cols_; j++) {
      matrix_result.matrix_[i][j] = 0.0;
      for (int k = 0; k < cols_; k++) {
        matrix_result.matrix_[i][j] += matrix_[i][k] * matrix(k, j);
      }
    }
  }
  this->~S21Matrix();
  CreateMatrix(matrix_result.rows_, matrix_result.cols_);
  *this = matrix_result;
}

// Метод транспонирования матрицы
S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix new_matrix(get_cols(), get_rows());
  for (int i = 0; i < get_cols(); i++) {
    for (int j = 0; j < get_rows(); j++) {
      new_matrix.matrix_[i][j] = matrix_[j][i];
    }
  }
  return new_matrix;
}

// Метод нахождения матрицы алгебраических дополнений
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }
  S21Matrix result_matrix(rows_, cols_);
  if (rows_ == 1) {
    result_matrix(0, 0) = 1;
  } else {
    S21Matrix* buffer = new S21Matrix(rows_, rows_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        MinorSearch(matrix_, buffer->matrix_, i, j, rows_);
        result_matrix.matrix_[i][j] = pow(-1, i + j) * DeterminantSearch(buffer, rows_ - 1);
      }
    }
    delete buffer;
  }
  return result_matrix;
}

// Метод нахождения детерминанта матрицы
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    result = DeterminantSearch(this, rows_);
  }
  return result;
}

// Метод инверсии матрицы
S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (!determinant) {
    throw std::logic_error("Inverse matrix doesn't exist");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result(0, 0) = 1 / determinant;
  } else {
    S21Matrix minor = CalcComplements();
    S21Matrix transpose = minor.Transpose();
    transpose.MulNumber(1 / determinant);
    result = transpose;
  }
  return result;
}
